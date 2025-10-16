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

![Network Topology](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcShvr9FdmKNDoUqUF9v9rImarZwRG478Caaew&s)

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
  `rc = MPI_XXX(parameter, ...)`
- **Initialization and Termination:**  
  Must call `MPI_Init()` before any MPI function and `MPI_Finalize()` at the end.
- **Error Handling:**  
  Return value `rc = MPI_SUCCESS` if successful.
- **Arguments:**  
  Some arguments are passed by pointer; others are returned by value.

#### Communicators and Groups
- A **group** defines the collection of processes that can communicate with each other.
- Each group is associated with a **communicator**.
- `MPI_COMM_WORLD` is the predefined communicator that includes all processes.

#### Rank
- Each process has a **unique identifier** (task ID) within a communicator.
- Ranks start from zero and are contiguous.
- Used to distinguish between different processes.

---

### Environment Management Routines

- **`MPI_Init()`**  
  Initializes(Set up) the MPI execution environment.

- **`MPI_Finalize()`**  
  Terminates(Tear down) the MPI execution environment.

- **`MPI_Comm_size(comm, &size)`**  
  Determines the total number of processes in the communicator group.

- **`MPI_Comm_rank(comm, &rank)`**  
  Determines the  rank (task ID) of the calling process within the communicator.  
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