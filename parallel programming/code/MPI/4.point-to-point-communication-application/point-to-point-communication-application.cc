// Copyright 2011 www.mpitutorial.com
// Run the command by 
// mpicxx -std=c++11 point-to-point-communication-application.cc -o point-to-point-communication-application
// mpirun -np 2 ./point-to-point-communication-application 100 20 5

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

using namespace std;

typedef struct {
    int location;
    int steps_left;
} Walker;

void decompose_domain(int domain_size, int world_rank, int world_size, int* subdomain_start, int* subdomain_size) {
    if (world_size > domain_size) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    *subdomain_start = (domain_size / world_size) * world_rank;
    *subdomain_size = domain_size / world_size;
    if (world_rank == world_size - 1) {
        *subdomain_size += domain_size % world_size;
    }
}

void initialize_walkers(int num_walkers_per_process, int max_walk_size, int subdomain_start, vector<Walker>* incoming_walkers) {
    for (int i = 0; i < num_walkers_per_process; ++i) {
        Walker w;
        w.location = subdomain_start;
        w.steps_left = rand() % (max_walk_size + 1); // 0..max_walk_size
        incoming_walkers->push_back(w);
    }
}

void walk(Walker* walker, int subdomain_start, int subdomain_size, int domain_size, vector<Walker>* outgoing_walkers) {
    while (walker->steps_left > 0) {
        // subdomain covers [subdomain_start, subdomain_start + subdomain_size - 1]
        // If walker.location == subdomain_start + subdomain_size -> it's already beyond this subdomain
        if (walker->location >= subdomain_start + subdomain_size) {
            // wrap-around if beyond domain end
            if (walker->location >= domain_size) {
                walker->location = 0;
            }
            outgoing_walkers->push_back(*walker);
            break;
        } else {
            walker->steps_left--;
            walker->location++;
            // If after increment we landed exactly at subdomain boundary, next loop will handle outgoing
        }
    }
}

void send_outgoing_walkers(vector<Walker>* outgoing_walkers, int world_rank, int world_size) {
    void* buf = nullptr;
    int bytes = 0;
    if (!outgoing_walkers->empty()) {
        buf = (void*)outgoing_walkers->data();
        bytes = (int)(outgoing_walkers->size() * sizeof(Walker));
    }
    int dest = (world_rank + 1) % world_size;
    MPI_Send(buf, bytes, MPI_BYTE, dest, 0, MPI_COMM_WORLD);
    outgoing_walkers->clear();
}

void receive_incoming_walkers(vector<Walker>* incoming_walkers, int world_rank, int world_size) {
    MPI_Status status;
    int incoming_rank = (world_rank == 0) ? world_size - 1 : world_rank - 1;

    // Probe for incoming message (tag=0)
    MPI_Probe(incoming_rank, 0, MPI_COMM_WORLD, &status);

    int incoming_bytes;
    MPI_Get_count(&status, MPI_BYTE, &incoming_bytes);
    if (incoming_bytes == 0) {
        incoming_walkers->clear();
        return;
    }
    int incoming_count = incoming_bytes / (int)sizeof(Walker);
    incoming_walkers->resize(incoming_count);
    MPI_Recv((void*)incoming_walkers->data(), incoming_bytes, MPI_BYTE, incoming_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

int main(int argc, char** argv) {
  int domain_size;
  int max_walk_size;
  int num_walkers_per_proc;

  if (argc < 4) {
    cerr << "Usage: random_walk domain_size max_walk_size "
         << "num_walkers_per_proc" << endl;
    exit(1);
  }
  domain_size = atoi(argv[1]);
  max_walk_size = atoi(argv[2]);
  num_walkers_per_proc = atoi(argv[3]);

  MPI_Init(NULL, NULL);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  srand(time(NULL) * world_rank);
  int subdomain_start, subdomain_size;
  vector<Walker> incoming_walkers, outgoing_walkers;

  // Find your part of the domain
  decompose_domain(domain_size, world_rank, world_size,
                   &subdomain_start, &subdomain_size);
  // Initialize walkers in your subdomain
  initialize_walkers(num_walkers_per_proc, max_walk_size, subdomain_start,
                     &incoming_walkers);

  cout << "Process " << world_rank << " initiated " << num_walkers_per_proc
       << " walkers in subdomain " << subdomain_start << " - "
       << subdomain_start + subdomain_size - 1 << endl;

  // Determine the maximum amount of sends and receives needed to
  // complete all walkers
  int maximum_sends_recvs = max_walk_size / (domain_size / world_size) + 1;
  for (int m = 0; m < maximum_sends_recvs; m++) {
    // Process all incoming walkers
    for (int i = 0; i < incoming_walkers.size(); i++) {
       walk(&incoming_walkers[i], subdomain_start, subdomain_size,
            domain_size, &outgoing_walkers);
    }
    cout << "Process " << world_rank << " sending " << outgoing_walkers.size()
         << " outgoing walkers to process " << (world_rank + 1) % world_size
         << endl;
    if (world_rank % 2 == 0) {
      // Send all outgoing walkers to the next process.
      send_outgoing_walkers(&outgoing_walkers, world_rank,
                            world_size);
      // Receive all the new incoming walkers
      receive_incoming_walkers(&incoming_walkers, world_rank,
                               world_size);
    } else {
      // Receive all the new incoming walkers
      receive_incoming_walkers(&incoming_walkers, world_rank,
                               world_size);
      // Send all outgoing walkers to the next process.
      send_outgoing_walkers(&outgoing_walkers, world_rank,
                            world_size);
    }
    cout << "Process " << world_rank << " received " << incoming_walkers.size()
         << " incoming walkers" << endl;
  }
  cout << "Process " << world_rank << " done" << endl;
  MPI_Finalize();
  return 0;
}