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
- Typical workflow: **Host → Input Assembler → Thread Execution Manager → Processing Units (PBSM)**.  
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
  Smaller diameter → lower latency.

- **Bisection (Resilience)**  
  The minimum number of links that must be removed to divide the network into two disconnected parts.  
  Higher bisection → better fault tolerance.

- **Links (Cost)**  
  The total number of physical links required to connect all nodes.  
  More links → higher cost but potentially higher performance.

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
  - A multidimensional cube topology with \( N = 2^k \) nodes, where each node connects to \( k = \log_2 N \) other nodes.  
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
  - Data first transferred from **I/O node (server layer)** → **storage node** after buffering.  
- Characteristics:
  - **Buffers reside in I/O nodes**, decoupling compute and storage timing.  
  - Enables **steady throughput**, facilitating **I/O scheduling and reservation**.  
  - Uses **non-volatile memory (NVRAM)** — provides large capacity and **data persistence** even after system faults.

**Summary:**  
Parallel file systems and burst buffering are essential components of HPC I/O architecture, combining distributed data access with temporary buffering to achieve both **high bandwidth** and **low latency** in data-intensive workloads.

---

## Parallel Program Analysis

### Speedup Factor
- Program speedup factor: S(p) = Ts / Tp, Ts: execution time using BSET sequential algorithm, Tp: execution time using p processor
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
