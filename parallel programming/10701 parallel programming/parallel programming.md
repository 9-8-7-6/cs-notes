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
