# Parallel Programming

## What is Parallel Computing?
    Solve a single problem by using multiple processors (e.g., CPU cores, GPUs) working together.  

- Traditionally, programs were written for **serial computing**: one instruction at a time on a single processor.  
- **Parallel computing** allows tasks to be divided into smaller subtasks, executed **simultaneously** to improve performance.  

---

## Difference Between Parallel Computing & Distributed Computing

### Parallel Computing
- Runs a **single application** spread across multiple processors/cores.  
- Goal: **speed up execution** and handle larger computations.  
- Example: Using OpenMP to parallelize a matrix multiplication across 8 CPU cores.  

### Distributed Computing
- Runs activities across **multiple independent systems** or geographically separated servers.  
- Goal: **concurrency** and **resource sharing**, not only performance.  
- Many machines cooperate, often focusing on **scalability and fault tolerance**.  
- Example: Hadoop or Spark jobs spread across a cluster of machines.  

---

## Why Need Parallel Computing
- **Save time**  
  Use more resources to shorten execution, potentially reducing costs.  

- **Solve larger problems**  
  Some problems are impossible or impractical to solve on a single computer.  

---

## Parallel Computer Classification  

### Flynn's Classic Taxonomy
Flynn’s taxonomy classifies computer architectures from the **processing unit perspective**, based on two independent dimensions: **Instruction** and **Data**.  

---

### 1. SISD (Single Instruction, Single Data)  
- **A serial computer**.  
- **Single Instruction**: Only one instruction stream is executed by the CPU per clock cycle.  
- **Single Data**: Only one data stream is processed per clock cycle.  
- Example: Traditional single-core CPU.  

---

### 2. SIMD (Single Instruction, Multiple Data)  
- All processing units execute the **same instruction** simultaneously.  
- The processor may be composed of a single control unit and multiple datapaths.
- **Multiple Data**: Each processing unit works on a different element of the data.  
- Example: GPUs, vector processors.  

---

### 3. MISD (Multiple Instruction, Single Data)  
- **Multiple Instructions**: Each processing unit executes a different instruction.  
- **Single Data**: The same single data stream is fed into all processing units.  
- Rare in practice, mainly theoretical or used in specialized systems (e.g., fault-tolerant systems).  

---

### 4. MIMD (Multiple Instruction, Multiple Data)  
- **Multiple Instructions**: Each processor executes its own instruction stream.  
- **Multiple Data**: Each processor works with different data.  
- Example: Most modern multi-core CPUs and distributed systems.  

---

## Memory Architecture Classification  

Parallel computer architectures can also be classified based on **how processors access memory**.  

---

### 1. Distributed Memory
- Connect multiple computers to form a computing platform without sharing.
- Each CPU (or processor) has its **own memory and address space**.
- Processors communicate by passing messages (e.g., MPI).  
- Common in **clusters**, **Supercomputer**, **large-scale distributed systems**, and **data center**.

---

### 2. Shared Memory  
- All CPUs share the **same global memory space**.  
- Easier for programmers (no need for explicit message passing), but may suffer from memory contention.  

#### 2.1 Uniform Memory Access (UMA)  
- All CPUs have **equal access time** to memory.  
- Common in **symmetric multiprocessing (SMP)** systems.  

#### 2.2 Non-Uniform Memory Access (NUMA)  
- Physically links two or more SMPs.  
- A CPU can directly access its local memory quickly, but accessing remote memory across the interconnect is **slower**.  
- Common in **high-performance computing (HPC) servers**.  

---

![Shared memory architecture](https://techplayon.com/wp-content/uploads/2019/10/1.png)  

---

## Parallel Programming Model  

Parallel programming models provide an **abstraction layer** above the hardware and memory architecture.  
They are designed to **match** the underlying computer architecture but are **not strictly restricted** by it.  

- **Shared memory programming model**: Used for shared memory machines.  
- **Message passing programming model**: Used for distributed memory machines.  
- Threads communicate with each other through **global memory**.  
- Implementations can be:  
  - **Low-level libraries** of subroutines (e.g., POSIX Threads).  
  - **Compiler directives** embedded in source code (e.g., OpenMP).  

---

### Message Passing Programming Model  
- Tasks exchange data explicitly by **sending and receiving messages** (data copied between memories).  
- Common MPI (Message Passing Interface) APIs include:  
  - `Send`, `Recv`, `Bcast`, `Gather`, `Scatter`, etc.  

---

### Notes  
- The **design and popularity** of programming models and parallel systems are highly interdependent.  
- Widely used parallel programming frameworks/languages include:  
  - **OpenMP**, **MPI**, **Pthreads**, **CUDA**.  
- **Understanding parallel computing concepts** is more important than just learning parallel programming syntax.  

---

### HPL Benchmark
- Measures the **floating-point rate of execution**.  
- Solves a large **linear system of equations** \( Ax = b \).  
- Performs **LU factorization** via **panel factorization**.  
- Divides the matrix into **multiple sub-blocks (tiles)** for distributed parallel computation.  

---

### Limitation of General-Purpose CPU
- A **general-purpose CPU** is flexible and capable of handling various tasks,  
  but its architecture is **not optimized** for specific high-performance workloads.  
- The **memory bandwidth** between the processor and main memory can become  
  a **bottleneck**, limiting overall computational performance.  

---

### NVIDIA General-Purpose GPU (GPGPU)
- Extends the **GPU** beyond graphics to act as a **stream processor (vector processor)** for general-purpose computing.  
- Well-suited for **embarrassingly parallel tasks** and **vectorized operations**.  
- Built on the **CUDA architecture**, allowing developers to write massively parallel programs in C/C++/Fortran.  
- Functions as an **accelerator** or **co-processor** working alongside the CPU (**host**).  
- Typical workflow: **Host -> Input Assembler -> Thread Execution Manager -> Processing Units (PBSM)**.  
- Employs **Global Memory** and **Constant Memory**, shared among many threads for coordinated data access.  
- **Scheduling** is handled **entirely by hardware**, allowing thousands of threads to execute concurrently.  
- The **memory access speed** often becomes the **performance bottleneck**, especially for memory-bound applications.  

### Intel Xeon Phi
- A **many-core processor** that runs **x86 instructions**, just like a standard Intel CPU.
- Can execute **Intel assembly code**, making it easier to port existing CPU-based applications.
- Operates under a **lightweight embedded Linux OS**, allowing direct execution of user applications.  
- Designed for **highly parallel workloads** such as scientific computing and simulations.  

---

### Google Tensor Processing Unit (TPU)
- A **domain-specific accelerator** designed by Google for **deep learning workloads** (especially TensorFlow).  
- Optimized for **matrix (tensor) operations**, focusing on **2D multiply-accumulate** computations.  
- Uses a **systolic array architecture**, enabling massive parallelism for neural network operations.  
- Unlike a CPU (which processes one element at a time), a TPU processes **entire matrices simultaneously**.  
- Provides extremely high **throughput** and **energy efficiency** for training and inference tasks.  

---

## Communication
- Data transfer between nodes (servers) is typically far slower than computation speed inside a CPU.  
- Communication is common to parallel programs.
- Synchronization is expensive and grow exponentially as the number of servers increase.
- More nodes are equal to more latency, more potential bottlenecks.

---

## Interconnection Networks
An **interconnection network** is the communication backbone that connects processors, memory modules, and I/O devices in a parallel or distributed system.

### Design Considerations
- **Scalability** – How easily can more nodes be added without major performance drops.  
- **Performance** – Measured in bandwidth and latency; higher is better.  
- **Resilience** – The ability to tolerate node or link failures (fault tolerance).  
- **Cost** – Hardware (switches, cables) and power consumption must remain economical.

---

## Interconnection Network Topology
Topology defines **how nodes are connected** to each other.

- **Network diameter** – The longest shortest path between any two nodes; smaller diameter = faster communication.  
- **Re-routing path for fault tolerance** – Alternate paths allow communication to continue even if a link fails.  
- **Fan-in / Fan-out degree per node** – Number of input/output connections each node can handle.

Common topologies include:
- **Bus** – Simple shared medium (low cost, low scalability).  
- **Ring** – Each node connects to two neighbors.  
- **Mesh / Torus** – Nodes arranged in 2D or 3D grids.  
- **Tree / Fat Tree** – Hierarchical, good for data centers.  
- **Hypercube** – High connectivity, low diameter.  
- **Fully connected** – Fastest but most expensive.

---

## Network Devices
Hardware components used to implement interconnection networks:

- **Cable** : Physical link for data transmission.
- **Switch** : Routes packets between nodes.
- **Network Adapter** : Interface between node and network.

---

## Network Topology

- **Diameter (Latency)**  
  The maximum number of hops between any two nodes in the network.  
  Smaller diameter -> lower latency.

- **Bisection (Resilience)**  
  The minimum number of links that must be removed to divide the network into two disconnected parts.  
  Higher bisection -> better fault tolerance.

- **Links (Cost)**  
  The total number of physical links required to connect all nodes.  
  More links -> higher cost but potentially higher performance.

---

### Common Topologies

![Network Topology](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcShvr9FdmKNDoUqUF9v9rImarZwRG478Caaew&s)

- **Linear Array**  
  - Simplest and cheapest design.  
  - Nodes connected in a straight line.  
  - High latency and poor reliability — a single link failure can partition the network.

- **Ring**  
  - Each node connected to two neighbors, forming a closed loop.  
  - Moderate reliability — can reroute traffic in the opposite direction if one link fails.  
  - Suitable for small to medium systems.

- **Tree**  
  - Hierarchical structure with parent-child relationships.  
  - Scalable and easy to expand.  
  - Vulnerable to root or upper-level link failures.

- **2-D Mesh**  
  - Nodes arranged in a grid; each connected to up to four neighbors (north, south, east, west).  
  - Good balance of latency, scalability, and reliability.  
  - Common in modern multi-core and distributed systems.

- **Torus**  
  - An extension of the 2-D mesh where opposite edges are connected, forming a “wrap-around” network.  
  - Every node has the same number of neighbors, maintaining uniform latency.  
  - Reduces edge congestion compared to mesh topology.  
  - Frequently used in large-scale parallel supercomputers.

- **Hypercube**  
  - A multidimensional cube topology with \( N = 2^k \) nodes, where each node connects to \( k = log_2 N \) other nodes.  
  - Short average path length — at most \( k \) hops between any two nodes.  
  - High connectivity and fault tolerance.  
  - Complex wiring and expensive implementation for large systems.  
  - Common in parallel computers and message-passing multiprocessors (e.g., network switches or interconnect fabrics).

---

### InfiniBand

- A **computer network communication link protocol** used in **high-performance computing (HPC)**, featuring **very high throughput** and **low latency**.  
- More used in shared environments, **InfiniBand reservations take priority** to ensure deterministic performance.  
- Based on **RDMA (Remote Direct Memory Access)** , which allows data to be transferred **directly between memory buffers** of different nodes **without involving the CPU or operating system**, reducing overhead and latency.  
- Commonly used as the **interconnect fabric** in **supercomputers**, **AI clusters**, and **large-scale distributed systems**.  

---

## I/O & Storage Technology

### Parallel File and I/O Systems
- Designed to handle **large-scale concurrent data access** in high-performance computing (HPC) environments.  
- Distribute both data and metadata across multiple storage servers to increase throughput and scalability.  
- Common implementations:
  - **Lustre File System** — a widely used parallel file system in supercomputers.  
  - **MPI-IO** — a standardized parallel I/O interface defined by MPI, enabling coordinated data access among processes.  
- Components:
  - **OST (Object Storage Target)** — stores actual file data.  
  - **MDS (Metadata Server)** — manages metadata such as file names, directories, and access permissions.  
- Storage typically contains:
  - **Metadata** — information about file structure and access.  
  - **Dictionary data** — mapping between logical and physical storage layout.

---

### Burst Buffering
- Introduces **non-volatile memory (NVRAM)** at I/O server nodes to act as a **temporary buffer**.  
- Purpose:
  - Smooth out **burst traffic patterns** caused by simultaneous I/O requests from many compute nodes.  
  - Improve overall **I/O performance** and **reduce storage latency**.  
- Data flow:
  - **Compute nodes** -> **I/O nodes (NVRAM buffer)** -> **storage node**.  
- Characteristics:
  - **Buffers reside in I/O nodes**, decoupling compute and storage timing.  
  - Enables **steady throughput**, facilitating **I/O scheduling and reservation**.  
  - Uses **non-volatile memory (NVRAM)** — provides large capacity and **data persistence** even after system faults.

**Summary:**  
Parallel file systems and burst buffering are essential components of HPC I/O architecture, combining distributed data access with temporary buffering to achieve both **high bandwidth** and **low latency** in data-intensive workloads.

---

## Parallel Program Analysis

### Speedup Factor
- Program speedup factor: S(p) = Ts / Tp, Ts: execution time using BEST sequential algorithm, Tp: execution time using p processor
- Linear speedup: S(p) = p.
  - ideal maximum speedup in the theory.
- Superlinear speedup: S(p) > p
  - Extra Hardware resource(i.g. memory).
  - SW or HW optimization(i.g. caching).
- System efficiency: E(p) = Ts / (Tp * p) = s(p) / p * 100%.

## 2. Maximum Speedup

Achieving the ideal \( S(p) = p \) is challenging because:
- Not every part of the computation can be parallelized (some processors remain idle).  
- Parallel versions often require **extra computation** for data partitioning or synchronization.  
- **Communication overhead** between processes is typically the dominant performance bottleneck.

### Strong Scaling
- The problem size stays fixed but the number of processing elements are increased.
- It is used to find the **sweet spot** that allows the computation to complete in a reasonable amount of time.
- Core must be large enough to achive strong scaling.
- Communicateion overhead may increase as the scale increase so hard to achieve.

### Weak Scaling
- The **workload per processor** remains constant as the number of processors increases.  
- **Linear weak scaling** occurs when runtime stays constant while total workload increases proportionally.  
- Easier to achieve than strong scaling since each processor handles a fixed workload.  
- **External communication** decreases, but **internal communication** among processors increases.

---

### Time Complexity Analysis
- Tp = Tcomp + Tcomm
  - Tp: Total execution time of a parallel algorithm
  - Tcomp: Computation part
  - Tcomm: Communication part

- Tcomm = q(Tstartup + nTdata)
  - Tstartup = Message latency (assumed constant)
  - Tdata = Transmission time per data item
  - n = Number of data items per message
  - q = Number of messages sent

---

## MPI (Message Passing Interface)

### Overview
- **Definition:** A specification for message passing libraries.
- **Purpose:** Commonly used for distributed memory systems and high-performance computing.
- **Architecture:**
  - MPI Programmer (Program) -> **MPI Interface** -> MPI Developer (MPI Library: MPICH)
- **Goals:**
  - **Portable:** Run on different machines.
  - **Scalable:** Run on millions of compute nodes.
  - **Flexible:** Isolate MPI developers from MPI programmers (users).

---

### Programming Model

#### SPMD (Single Program Multiple Data)
- All tasks run the same program but may execute different parts based on their role.
- Tasks can conditionally branch to perform different operations.
- MPI tasks cannot be dynamically spawned during runtime.
- Each task is assigned a unique ID when the library creates it.

#### Distributed Memory
- Each process has its own memory space.
- MPI provides methods for sending and receiving messages between these processes.

---

### Communication Methods

#### View from Communicated Processes
- **Synchronous Communication:**  
  Sending and receiving occur simultaneously.
- **Asynchronous Communication:**  
  Sending and receiving occur independently at different times.

#### View from Function Calls
- **Blocking:**  
  The routine does not return until the data transfer is completed.
- **Non-Blocking:**  
  The routine returns immediately, allowing the program to continue execution.

#### Synchronous / Blocking Message Passing
- **Sender:** Waits until the entire message is accepted by the receiver.  
- **Receiver:** Waits until the expected message arrives.

#### Asynchronous / Non-Blocking Message Passing
- Uses a **message buffer** as temporary memory space to hold messages.
- Buffers are managed by the MPI library.

---

### MPI API

#### MPI Calls
- **Format:**  
  `rc (return code) = MPI_XXX(parameter, ...)`
- **Initialization and Termination:**  
  Must call `MPI_Init()` before any MPI function and `MPI_Finalize()` at the end.
- **Error Handling:**  
  Return value `rc = MPI_SUCCESS` if successful.
- **Arguments:**  
  Some arguments are passed by pointer; others are returned by value.

#### Communicators and Groups
- A **communicator** is a collection of processes that can send messages to each
other, which is like objects of all processes.
- A **group** defines the collection of processes that can communicate with each other, which is like a list of processes.
- Each group is associated with a **communicator**.
- `MPI_COMM_WORLD` is the predefined communicator that includes all processes.

#### Rank
- Each process has a **unique identifier** (task ID) within a communicator.
- Ranks start from zero and are contiguous.
- Used to distinguish between different processes.

---

### Environment Management Routines

- **`MPI_Init()`**  
  - Initializes(Set up) the MPI execution environment.
  - This routine must be called by one thread only. That thread is called the main thread and must be the thread that calls MPI_Finalize.

- **`MPI_Finalize()`**  
  - Terminates(Tear down) the MPI execution environment.

- **`MPI_Comm_size(comm, &size)`**  
  - Determines the total number of processes in the communicator group.

- **`MPI_Comm_rank(comm, &rank)`**  
  - Determines the  rank (task ID) of the calling process within the communicator.  
  The rank identifies which process is executing.

---

#### Typical MPI Initialization

``` C
int main (int argc, char **argv) {
  int num_procs;
  int rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  printf("%d: hello (p=%d)\n", rank, num_procs);

  /* Do many things, all at one */

  MPI_Finalize();
}

```

---
 
### Point-to-Point Communication Routines

MPI provides routines for sending and receiving messages between individual processes. These routines can be **blocking** or **non-blocking** depending on whether they wait for communication to complete before returning.

---

#### Blocking Communication
- **Send:**  
  `MPI_Send(buffer, count, type, dest, tag, comm)`
- **Receive:**  
  `MPI_Recv(buffer, count, type, source, tag, comm, status)`
- comm == comm, tag == tag

Blocking routines return only after the corresponding operation (send or receive) has completed.

---

#### Non-Blocking Communication
- Provide better performance because it allows **overlapping computation and communication**.  
- continue performing useful work while data is being transferred in the background, leading to improved efficiency on distributed systems.

- **Send:**  
  `MPI_Isend(buffer, count, type, dest, tag, comm, request)`
- **Receive:**  
  `MPI_Irecv(buffer, count, type, source, tag, comm, request)`

Non-blocking routines return immediately, allowing the program to continue execution while the operation completes in the background.  
The completion of these operations can later be checked using the **request** handle.

---

#### Parameters

- **buffer**  
  Address of the memory space containing the data to be sent or received.  
  Must be allocated before calling MPI routines.

- **count**  
  Number of data elements (of the specified type) to send or receive.

- **type**  
  Data type of elements. Examples:  
  `MPI_CHAR`, `MPI_SHORT`, `MPI_INT`, `MPI_LONG`, `MPI_DOUBLE`, etc.

- **comm**  
  Communicator that defines the context for communication (e.g., `MPI_COMM_WORLD`).

- **source / dest**  
  Rank (task ID) of the sending or receiving process.

- **tag**  
  Arbitrary non-negative integer assigned by the programmer to identify messages.  
  The sender and receiver must use matching tags for successful communication.  
  `MPI_ANY_TAG` can be used as a wildcard for receiving.

- **status**  
  Contains information about a completed receive operation (e.g., message source, tag, count).

- **request**  
  Handle used by non-blocking operations to track progress or completion status.

---

## Collective Communication Routines

Collective communication routines involve **all processes** within a communicator.  
Unlike point-to-point communication, collective routines synchronize data exchange or computation across multiple processes simultaneously.

---

### 1. `MPI_Barrier(comm)`
- **Purpose:** Creates a synchronization barrier among all processes in a communicator.  
- **Behavior:**  
  - Each process blocks at the barrier until **all** processes have reached the same `MPI_Barrier` call.  
  - Ensures all processes are synchronized before continuing execution.

---

### 2. `MPI_Bcast(&buffer, count, datatype, root, comm)`
- **Purpose:** Broadcasts a message from one process (**root**) to all other processes in the communicator.  
- **Behavior:**  
  - The process with rank `root` sends the contents of its buffer to every other process.  
  - Example:  
    If `root = 1` and `count = 1`, the process with rank `1` broadcasts its buffer to all others.

---

### 3. `MPI_Scatter(&sendbuf, sendcnt, sendtype, &recvbuf, recvcnt, recvtype, root, comm)`
- **Purpose:** Distributes **different portions of data** from one root process to all processes in the group.  
- **Behavior:**  
  - The root’s `sendbuf` is divided into segments, each sent to a corresponding process.  
  - Each process receives its segment into its `recvbuf`.  
  - Conceptually: `sendbuf → recvbuf (per process)`

---

### 4. `MPI_Gather(&sendbuf, sendcnt, sendtype, &recvbuf, recvcnt, recvtype, root, comm)`
- **Purpose:** Collects data from all processes and gathers them into one destination process (the **root**).  
- **Behavior:**  
  - Each process sends its local `sendbuf` to the root process.  
  - The root combines all received data into its `recvbuf`.  
  - Commonly used to aggregate computed results.  
  - Conceptually: `sendbuf (from each process) → recvbuf (at root)`

---

### 5. `MPI_Reduce(&sendbuf, &recvbuf, count, datatype, op, dest, comm)`
- **Purpose:** Performs a **reduction operation** (e.g., sum, max, min) across all processes and stores the result in one destination process.  
- **Parameters:**  
  - `op`: Operation type (e.g., `MPI_SUM`, `MPI_MAX`, `MPI_MIN`, etc.)  
  - `dest`: The rank of the process where the reduced result is stored.  
- **Example:**  
  `dest = 2`, `count = 1`, `op = MPI_SUM` → all values are summed and stored in process rank 2.

---

### 6. `MPI_Allgather(&sendbuf, sendcount, sendtype, &recvbuf, recvcount, recvtype, comm)`
- **Purpose:** Gathers data from all processes and distributes the complete result to **every** process.  
- **Behavior:**  
  - Each process collects data from all others.  
  - Functionally equivalent to performing an `MPI_Gather` followed by an `MPI_Bcast`.  
  - Every process ends up with the same concatenated result.

---

### 7. `MPI_Allreduce(&sendbuf, &recvbuf, count, datatype, op, comm)`

- **Purpose:**  
  Performs a **reduction operation** (such as sum, maximum, or minimum) across all processes in a communicator,  
  and then **distributes the final result to every process**.

- **Behavior:**  
  - Each process provides its own input data in `sendbuf`.  
  - MPI combines all the data across processes using the specified operation (`op`).  
  - The result of this reduction is stored in `recvbuf` **on every process**, not just one.  
  - Functionally equivalent to performing an `MPI_Reduce` followed by an `MPI_Bcast`.

---

## Group and Communicator Routines

MPI allows processes to be organized into **groups** and **communicators**, defining which processes can communicate with each other and within what context.

### Group and Communicator Data Types
- **`MPI_Group`**  
  Represents a collection of processes. A group defines membership but does not allow direct communication.

- **`MPI_Comm`**  
  Represents a **communicator**, which enables communication among the processes in a group.  
  (A communicator is always created based on a group.)

---

### 1. `MPI_Comm_group(Comm, &Group)`
- **Purpose:**  
  Extracts the **group** associated with a given communicator.
- **Usage:**  
  Since MPI provides a default communicator (`MPI_COMM_WORLD`), this call is often used to obtain the default group from it.
- **Example:**  
  ```c
  MPI_Group group_world;
  MPI_Comm_group(MPI_COMM_WORLD, &group_world);
  ```

### 2. `MPI_Group_incl(Group, size, ranks[], &NewGroup)`

- Purpose:
Produces a new group by including a subset of members from an existing group.

- Parameters:
- Group: The original group.
- size: Number of processes to include in the new group.
- ranks[]: Array of process ranks (within the original group) to include.
- NewGroup: The resulting subgroup.

- Example: 
```c
  int ranks[2] = {0, 1};
  MPI_Group new_group;
  MPI_Group_incl(group_world, 2, ranks, &new_group);
```

### 3. MPI_Comm_create(Comm, NewGroup, &NewComm)

- Purpose:
  Creates a new communicator for the specified group of processes.

- Behavior:
  - The new communicator must be a subset of the original communicator.
  - Only the processes included in NewGroup can use NewComm for communication.

- Example:
```c
  MPI_Comm new_comm;
  MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);
```

---

## Data access

### POSIX File Access
- Model: 1-to-1 mapping between compute node and storage node.
- Limitation:
- Multiple processes writing to the same file may cause data inconsistency due to locking.
- To perform concurrent writes, multiple files are typically required — this makes it hard to manage and wastes the potential of parallel file systems.

### MPI-IO File Access
- Function: MPI_FILE_open()
  - MPI provides shared file handles and synchronizes access among processes via the MPI library.

### MPI-IO Independent/Collective I/O

- Collective I/O
  - All processes participate in the I/O operation collectively.
  - Data is gathered into a shared buffer, and a single file request is issued.
  - The MPI library maintains an internal I/O buffer for coordination.
  - Advantages:
    - Reduces number of I/O requests.
    - Efficient for small I/O.
  - Disadvantages:
    - Requires synchronization among processes.

- Independent I/O
  - Each process performs I/O independently.
  - No synchronization with other processes.
  - Each process issues its own file request.
  - Advantages:
    - Better suited for large, independent I/O.
  - Disadvantages:
    - Requests can be serialized when accessing the same OST (Object Storage Target).
    - May lead to write conflicts when accessing overlapping file regions.

---

## Shared-Memory Programming: Pthread

### Shared-Memory Programming
- Definition: Processes communicate or work together through a shared memory space which can be accessed by all processes.
- Issues:
  - Synchronization
  - Deadlock
  - Cache coherence
- Techniques:
  - Parallelizing compiler
  - Unix processes
  - Threads(Pthread, Java)

### Pthread
- **Pthread** is the implementation of the **POSIX standard for threads**.  
- The relationship between **Pthread** and **POSIX** is similar to that between **MPICH** and **MPI**.

---

### Pthread Creation
#### Function Prototype
```c
pthread_create(thread, attr, routine, arg)
```

#### Parameters
- thread — A unique identifier (token) for the new thread.
- attr — Thread attributes. Use `NULL` for default values.
- routine — The function (routine) that the thread will execute once created.
- arg — A single argument passed to the routine.
  
#### Notes 
- The created thread can read and modify values from the main thread.
- It can also return a value to the main thread.
- The argument (`arg`) can be a data structure, typically passed as a pointer.
- Be sure to cast data types appropriately when passing or receiving arguments.

#### Example 

```c
// pthread_example.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

// Thread routine: prints a greeting message with its thread ID
void *PrintHello(void *threadArg) {
    long tid = *(long *)threadArg;    // Extract thread ID
    printf("Hello World! It's me, thread #%ld\n", tid);
    return NULL;                      // Can return a pointer if needed (simplified as NULL here)
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    long thread_ids[NUM_THREADS];
    int rc;

    // Create threads
    for (long t = 0; t < NUM_THREADS; ++t) {
        thread_ids[t] = t; // Each thread gets its own ID slot to avoid race conditions
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&thread_ids[t]);
        if (rc != 0) {
            fprintf(stderr, "Error: pthread_create failed with code %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int t = 0; t < NUM_THREADS; ++t) {
        rc = pthread_join(threads[t], NULL);
        if (rc != 0) {
            fprintf(stderr, "Error: pthread_join failed with code %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    printf("All threads finished. Exiting main.\n");
    return 0;
}
```

### Pthread Joining & Detaching

#### `pthread_join(threadId, status)`
- **Purpose:**  
  The calling thread waits until the specified thread (`threadId`) terminates, optionally retrieving its return status.
- **Key points:**
  - It **blocks** the caller until the target thread finishes.
  - Used for **synchronization** between threads.
  - Common in scenarios where threads perform sub-tasks and their results need to be merged afterward.

  ```c
  pthread_join(thread, NULL);
  ```
- Example:
Several worker threads process data in parallel, and the main thread waits for all of them to finish before aggregating results.

#### `pthread_detach(threadId)`
- Purpose:
Marks a thread as detached, meaning its resources are automatically released when it terminates.

- Key points:
  - Once detached, a thread cannot be joined later.
  - Helps free system resources automatically when the thread finishes.
  - Common in server-like applications where threads handle independent tasks (e.g., each thread serves a client request).
  ```c
  pthread_detach(thread);
  ```
- Example:
A web server creates a new thread for each incoming request. Since each request is independent, threads are detached so they clean up automatically after completing their work.

---

### Synchronization Problem & Tools

The **outcome of shared data** should **not depend on the execution order** among processes or threads.  
Instructions of individual threads may be interleaved, leading to **race conditions** if synchronization is not properly handled.

---

#### Pthread Lock / Mutex Routines

- A mutex must be declared as type **`pthread_mutex_t`**, initialized with **`pthread_mutex_init()`**, and destroyed with **`pthread_mutex_destroy()`** when no longer needed.  
- A **critical section** — the code segment accessing shared memory or shared resources — can be protected using **`pthread_mutex_lock()`** and **`pthread_mutex_unlock()`** to ensure only one thread executes that section at a time.  
- Whenever shared memory or shared variables exist, those sections should be clearly identified and protected as **critical sections**.


```c
int counter;    // Initialize to 0
sem_t count_sem;    // Initialize to 1
sem_t barrier_sem;  // Initialize to 0

Void* Thread_work() {
    sem_wait(&count_sem);
    If (counter == thread_count - 1) {
        counter = 0;
        sem_post(count_sem);
        for ( j = 0; j < thread_count - 1; j ++) {
            sem_post(&barrier_sem);
        }
    } else {
        counter++;
        sem_post(&count_sem);
        sem_wait(&barrier_sem);
    }
}
```

---

#### Synchronization

For a detailed explanation of process synchronization concepts and common mechanisms (such as semaphores, monitors, and condition variables), refer to:

🔗 [Process Synchronization – CS Notes](https://github.com/9-8-7-6/cs-notes/blob/5c91b5169f01649dfaf308441a865811f4f75e0d/operating%20systems/06-process%20synchronization.md)

---

#### Condition Variables (CV) in Pthread

- Type is `pthread_cond_t`.
- A synchronization mechanism that allows threads to wait (sleep) until a specific condition becomes true, and be awakened by another thread.
- Common routines:
  - `pthread_cond_init()` — initialize a condition variable.
  - `pthread_cond_wait(&theCV, &somelock)` — release the lock and wait for a signal.
  - `pthread_cond_signal(&theCV)` — unlock one blocked thread.
  - `pthread_cond_broadcast(&theCV)` — unlock all blocked threads.

- Example
```c 
void action() {
    pthread_mutex_lock(&mutex);
    // --- Critical section start ---
    if (x != 0) {
        pthread_cond_wait(&cond, &mutex);
    }
    // --- Critical section end ---
    pthread_mutex_unlock(&mutex);

    take_action();
}
```

```c
void counter() {
    pthread_mutex_lock(&mutex);
    x--;
    if (x == 0) {
        pthread_cond_signal(&cond);
    }
    pthread_mutex_unlock(&mutex);
}
```

##### Explanation

- The event counter **x** is a shared variable among threads.

If no lock is used in **action()**:
- A thread may call **pthread_cond_wait()** after another thread has already set **x = 0**, causing it to miss the signal and block indefinitely.

If no lock is used in **counter()**:

There is no guarantee that the decrement and test of **x** occur atomically, leading to race conditions.

By requiring condition variable operations to be performed while holding a mutex lock, Pthread prevents many common synchronization bugs and ensures safe access to shared state.

---

#### Thread Pools
- Create a number of threads in a pool where they await work.

```c
// thread_pool_example.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 4
#define MAX_QUEUE   10

typedef struct {
    void (*function)(void *arg);
    void *arg;
} task_t;

typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_t threads[MAX_THREADS];
    task_t queue[MAX_QUEUE];

    int queue_size;
    int head;
    int tail;
    int count;
    int shutdown;
} thread_pool_t;

// Worker thread routine
void *thread_do_work(void *pool_arg) {
    thread_pool_t *pool = (thread_pool_t *)pool_arg;

    while (1) {
        pthread_mutex_lock(&pool->lock);

        // Wait for available tasks or shutdown
        while (pool->count == 0 && !pool->shutdown) {
            pthread_cond_wait(&pool->notify, &pool->lock);
        }

        if (pool->shutdown) {
            pthread_mutex_unlock(&pool->lock);
            pthread_exit(NULL);
        }

        // Fetch task from queue
        task_t task = pool->queue[pool->head];
        pool->head = (pool->head + 1) % pool->queue_size;
        pool->count--;

        pthread_mutex_unlock(&pool->lock);

        // Execute task
        (*(task.function))(task.arg);
    }

    pthread_exit(NULL);
}

// Create thread pool
thread_pool_t *thread_pool_create(int num_threads, int queue_size) {
    thread_pool_t *pool = (thread_pool_t *)malloc(sizeof(thread_pool_t));
    if (!pool) return NULL;

    pool->queue_size = queue_size;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = 0;

    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->notify, NULL);

    for (int i = 0; i < num_threads; ++i) {
        pthread_create(&pool->threads[i], NULL, thread_do_work, (void *)pool);
    }

    return pool;
}

// Add task to pool
int thread_pool_add(thread_pool_t *pool, void (*function)(void *), void *arg) {
    pthread_mutex_lock(&pool->lock);

    if (pool->count == pool->queue_size) {
        pthread_mutex_unlock(&pool->lock);
        return -1; // queue full
    }

    // Add task
    pool->queue[pool->tail].function = function;
    pool->queue[pool->tail].arg = arg;
    pool->tail = (pool->tail + 1) % pool->queue_size;
    pool->count++;

    pthread_cond_signal(&pool->notify);
    pthread_mutex_unlock(&pool->lock);

    return 0;
}

// Destroy thread pool
void thread_pool_destroy(thread_pool_t *pool) {
    pthread_mutex_lock(&pool->lock);
    pool->shutdown = 1;
    pthread_cond_broadcast(&pool->notify);
    pthread_mutex_unlock(&pool->lock);

    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(pool->threads[i], NULL);
    }

    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->notify);
    free(pool);
}

// Example task
void example_task(void *arg) {
    int id = *(int *)arg;
    printf("Thread %lu is processing task %d\n", pthread_self(), id);
    sleep(1);
}

int main() {
    thread_pool_t *pool = thread_pool_create(MAX_THREADS, MAX_QUEUE);

    int tasks[20];
    for (int i = 0; i < 20; ++i) {
        tasks[i] = i;
        if (thread_pool_add(pool, example_task, &tasks[i]) != 0) {
            printf("Task queue full, skipping task %d\n", i);
        }
    }

    sleep(5); // Allow time for threads to process tasks
    thread_pool_destroy(pool);

    printf("All threads have completed. Exiting main.\n");
    return 0;
}
```

#### Pthread Semaphore
Semaphore is part of the POSIX standard, but it is **not** part of the Pthread library.  

##### POSIX Semaphore Routines
- `sem_init(sem_t *sem, int pshared, unsigned int value)`
- `sem_wait(sem_t *sem)`
- `sem_post(sem_t *sem)`
- `sem_getvalue(sem_t *sem, int *valptr)`
- `sem_destroy(sem_t *sem)`

##### Example
```c
#include <semaphore.h>
sem_t sem;

sem_init(&sem, 0, 1);  // Initialize semaphore with value 1
sem_wait(&sem);        // Enter critical section
  // critical section
sem_post(&sem);        // Exit critical section
sem_destroy(&sem);     // Clean up
```

##### Semaphore Drawbacks
- Its correctness depends on the programmer.
- All processes accessing shared data must execute `wait()` and `signal()` in the correct order and location.
- Programming errors or uncooperative behavior can break correctness easily.

#### Monitor
- A monitor is a high-level synchronization construct that simplifies shared data access.
- Instead of explicitly using wait() and signal(), the programmer defines a class with methods that manage shared data safely.
- The monitor guarantees that only one thread can access the shared data at a time, equivalent to a critical section.
- This approach provides high-level synchronization and reduces programmer error.

Synchronized Tools in Java
Synchronized Methods (Monitor)
- A synchronized method uses the method receiver (the object itself) as a lock.
- Two synchronized methods on the same object cannot interleave.
- When a thread executes a synchronized method, other threads calling any synchronized method on the same object are blocked.

```c
public class SynchronizedCounter {
  private int c = 0;

  public synchronized void increment() {
    c++;
  }

  public synchronized void decrement() {
    c--;
  }

  public synchronized int value() {
    return c;
  }
}
```

Synchronized Statements (Mutex Lock)
- A synchronized block uses a specific expression (object) as a lock.
- The block executes only when the thread has obtained the lock for that object.
- This approach improves concurrency through finer-grained locking.

``` c
public void run() {
  synchronized(p1) {
    int i = 10; // statement without locking requirement
    p1.display(s1);
  }
}
```

## OpenMP

**OpenMP (Open Multi-Processing)** is an API that supports **multi-threaded, shared-memory parallelism** in C, C++, and Fortran.

---

### Overview

- **API Type:** Multi-threaded, shared memory parallelism  
- **Portability:** Works across C/C++ and Fortran compilers  
- **Model:** Follows the *Fork-Join* model  
  - The master thread forks a number of slave threads.
  - Tasks are divided among these threads.
  - Threads rejoin the master after completing their work.
- **Compiler Directive-Based:**  
  The compiler interprets OpenMP directives to automatically create, manage, and synchronize threads.
- **Compile command:**
```c
  gcc -g -Wall -fopenmp -o hello_world hello_world.c
```

### Scope of variable
* **Shared scope**: A variable that all threads can access.
* **private scope**:A variable can only accessed by a single thread.
* Variables declared **before** a `parallel` directive are **shared** by default.
* Variables declared **inside** a `parallel` block (e.g., local variables in functions) are **private** by default.

### OpenMP Example

```c
#include <omp.h>

int A[10], B[10], C[10];

// Beginning of parallel section: Fork a team of threads
#pragma omp parallel for num_threads(10)
for (int i = 0; i < 10; i++) {
    A[i] = B[i] + C[i];
}
// Threads join back to the master after completion
```

### OpenMP Directives

- **C/C++ Format**
  - ```c
    #pragma omp    // Required
    ```
  - `directive-name`: Valid OpenMP directives include `parallel`, `do`, `for`, etc.  
  - `[clause, ...]`: Optional. Clauses can appear in any order and be repeated as needed.  
  - `newline`: Required to end the directive.  

- **Example**
  ```c
  #pragma omp parallel default(shared) private(beta, pi)
  ```

- Rules
  - Case sensitive.
  - Only one `directive-name` may be specified per directive.
  - Each directive applies to at most one succeeding statement, which must be a structured block.

#### Parallel Region
A parallel region is a block of code executed by multiple threads.

```c
#pragma omp parallel [clause...]
    if (scalar_expression)
    num_threads(integer_expression)
structured_block
```

#### Overview
- When the `parallel` directive is reached, a team of threads is created.
- The parallel region code is duplicated and executed by all threads.
- There is an implied barrier at the end of every parallel section (all threads must finish before continuing).
- If one thread crashes, **all threads in the team terminate**.

#### Limitations
- A **parallel region** must be a structured block that does not span multiple routines or source files.
- It is illegal to branch (`goto`) into or out of a parallel region.
- However, it is valid to call other functions within a parallel region.

### Parallel Region — Determining the Number of Threads

The number of threads in a parallel region is determined in the following order of precedence:

1. **Evaluation of the `if` clause**
   - If the expression evaluates to `FALSE`, the region is executed **serially** by the master thread.  
   - Example:  
     ```c
     #pragma omp parallel if(para == true)
     ```

2. **Setting of the `num_threads` clause**
   - Explicitly specifies the number of threads.  
   - Example:  
     ```c
     #pragma omp parallel num_threads(10)
     ```
3. **Calling the `omp_set_num_threads()` function**
   - Sets the number of threads **before** entering the parallel region.

4. **Setting the `OMP_NUM_THREADS` environment variable**
   - Also must be configured **before** the parallel region executes.

5. **Default behavior**
   - If none of the above are specified, the number of threads usually equals the **number of CPUs or cores** available on the node.

---

### Nested Parallel Regions

Example:
```c
// A total of 6 "hello world" messages will be printed
#pragma omp parallel num_threads(2)
{
  #pragma omp parallel num_threads(3)
  {
    printf("hello world!\n");
  }
}
```

- Check if nested parallelism is enabled:
```c
omp_get_nested();
```
- Enable or disable nested parallelism:
```c
omp_set_nested(bool);
```
Or set the environment variable:
```c
OMP_NESTED=true
```
- If nested parallelism is not supported or disabled:
  - Only one thread is created for the nested parallel region code (i.e., the nested region executes serially).

---

### Work-Sharing Construct

A **work-sharing construct** divides the execution of a specific code region among the threads that encounter it.  
It enables **parallel execution** of different parts of a program **without creating new threads**.

- Work-sharing constructs **do not launch new threads**; they use the existing threads.  
- There is **no implied barrier upon entry**, but there **is an implied barrier at the end** of each construct unless the `nowait` clause is used.

---

### Types of Work-Sharing Constructs

`A work-sharing construct defines how parallel tasks are divided and distributed among threads.`

#### 1. `for` / `do`

- Distributes loop iterations among threads.  
- Represents **data parallelism**, where each thread processes a different portion of an array or dataset.  
- Ideal when **loop iterations are independent** (no data dependency).

**Directive-specific clauses:**
- `nowait` — Do not synchronize threads at the end of the loop.  
- `schedule` — Describes how iterations are divided among threads.  
  - **static**  
    - Iterations are divided into fixed-size chunks.  
    - If chunk size is not specified, iterations are evenly divided among threads.  
  - **dynamic**  
    - Each thread dynamically grabs a new chunk after finishing one.  
  - **guided**  
    - Similar to dynamic, but chunk size decreases over time (for better load balancing).  
  - **runtime**  
    - The scheduling policy is determined at runtime via the environment variable `OMP_SCHEDULE`.  
  - **auto**  
    - The compiler decides the schedule type (not generally recommended).  
- `ordered` — Ensures that iterations are executed in the same order as in a serial version.  
- `collapse` — Specifies how many nested loops to combine into one iteration space.

**Example:**
```c
#pragma omp parallel for [clause... nowait/schedule/ordered/collapse ]
for (int i = 0; i < 100; i++) {
    A[i] = B[i] + C[i];
}
```


#### 2. `sections`
- A non-iterative work-sharing construct.
- Divides code into independent sections, **each SECTION is once executed by one thread**.
- Useful when tasks are distinct and can be performed concurrently.
**Example:**
```c
int N = 100;
int a[N], b[N], c[N], d[N];

#pragma omp parallel num_thread(2) shared(a, b, c, d) private(i)
{
  #pragma omp sections  // Specify sections
  {
      #pragma omp section   // 1st section
      { compute_A(); }

      #pragma omp section   // 2nd section
      { compute_B(); }

      #pragma omp section   // 3rd section
      { compute_C(); }
  }   // end of section
}   // end of parallel section
```

#### 3. `single`
- Only one thread executes a block of code.
- May be useful when dealing with sections of code not thread safe(such as I/O)
- Commonly used for I/O operations or initializing shared resources without locks.

**Example:**
```c
int input;
#pragma omp parallel num_thread(10) shared(input)
{
    #pragma omp single
    {
        printf("Initialization by one thread.\n");
        scanf("%d", &input);
    }
}
```

#### Summary:
- do / for → Divide loop iterations (data parallelism)
- sections → Divide tasks (task parallelism)
- single → Execute code by one thread only

---

### Types of Synchronization Construct

**Definition:**  
A *synchronization construct* controls how threads coordinate and safely access shared resources.

---

#### 1. `master`
- Executed **only** by the master thread.  
- Guarantees that a specific thread (the master) performs the enclosed code block.  
- **More efficient** than the `single` directive.  
- **No implicit barrier** at the end.

---

#### 2. `critical`
- Ensures that **only one thread** executes the enclosed section at a time.  
- Other threads are **blocked** until the critical section is released.  

---

#### 3. `barrier`
- All threads are **blocked** until **every thread** reaches the barrier.  
- Ensures synchronization points within parallel regions.

---

#### 4. `atomic`
- Guarantees that a specific **memory update** is performed **atomically**.  
- Provides a lightweight, **mini-critical section** for simple operations.  

---

### OpenMP Data Scope
**OpenMP is based on shared memory programming model**
- Most variables are shared by default
