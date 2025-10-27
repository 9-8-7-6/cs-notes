# Process Concept

## Program vs. Process
- **Program** – *passive*: binary stored on disk
- **Process** – *active*: program executed in memory

![Process Concept Diagram](https://cdn-images-1.medium.com/max/900/1*6vsoP1cWzQkN95AlEt2WoA.jpeg)

---

## Components of a Process
- **Code Segment (Text Section)** – program instructions  
- **Data Section** – global variables  
- **Stack** – temporary local variables, function calls  
- **Heap** – dynamically allocated memory (e.g., `malloc`, `new`)  
- **Program Counter (PC)** – register storing the address of the next instruction  
- **Resources** – e.g., open file handlers, I/O devices  

---

## Threads (Lightweight Processes)
- A **thread** is the basic unit of CPU utilization.  
- All threads of the same process share:
  - Code section  
  - Data section  
  - OS resources  
- Thread and process management are similar, but this chapter focuses on **processes**.  

---

## Process State (Virtual Concept)
![Process State Diagram](https://i.imgur.com/vD7tDw5.png)

- **New**: Process is being created (loaded into memory but not yet running).  
- **Ready**: Process is in memory, waiting in the queue to be assigned to the CPU.  
- **Running**: Instructions are being executed by the CPU.  
- **Waiting**: Process is waiting for an event (e.g., I/O completion).  
- **Terminated**: Process has finished execution, memory is freed.  

---

## Process Control Block (PCB)
![Process Control Block](https://cdn1.byjus.com/wp-content/uploads/2022/06/process-control-block.png)

- Stores the **current process state**.  
- The OS creates a PCB entry for **each process**.  
- Features:
  - Holds process information (state, PC, registers, memory limits, etc.).  

---

## Context Switch
- Switching the CPU from one process to another.  
- Triggered by:
  - **Interrupts** (e.g., I/O completion)  
  - **System calls** (e.g., keyboard/mouse events)  
- Steps:
  1. Save the current process state into its PCB.  
  2. Load the state of the next scheduled process.  

---

# Process Scheduling

## Multiprogramming
- Running several programs at the same time to improve CPU utilization.

## Time Sharing
- Frequent **context switches** so users can interact with the computer.

## Process Scheduling Queues
> Processes migrate between different scheduling queues.

- **Job Queue** – contains all new processes.  
- **Ready Queue** – processes waiting for CPU.  
- **Device Queue** – processes waiting for I/O devices.  

## Types of Schedulers
- **Short-term Scheduler (CPU Scheduler)**  
  - Frequently selects processes from **Ready → Running**.  
- **Long-term Scheduler (Job Scheduler)**  
  - Decides which jobs are loaded into memory from disk (**New → Ready**).  
- **Medium-term Scheduler**  
  - Performs **swapping**:
    - **Swap out**: Move processes from memory to disk (reduce degree of multiprogramming).  
    - **Swap in**: Reload swapped-out processes into memory.  
  - Related to **virtual memory management**.  

![Schedulers](https://afteracademy.com/images/what-is-longterm-shortterm-and-mediumterm-scheduler-longterm-shortterm-working.png)

---

# Operations on Processes

## Tree of Processes
- Each process has a **unique process identifier (PID)**.  
- Processes form a **parent–child hierarchy** (tree structure).  

## Resource Creation
- **Types of Resource Sharing Models**:  
  1. Parent and child share **all resources**.  
  2. Child shares a **subset** of parent resources.  
  3. Parent and child share **no resources**.  

- **Types of Memory Content**:  
  1. Child is a **duplicate** of the parent.  
  2. Child has a **new program loaded** into it.  

### UNIX/Linux Process Creation
- **fork()** system call  
  - Creates a duplicate of parent.  
  - Parent and child execute concurrently.  
  - Child returns **0**, Parent returns **PID** of child.  

- **execlp()** system call  
  - Loads a new binary into process memory space.  

- **wait()** system call  
  - Parent waits for one of its children to complete.  

### Process Termination
- A process terminates when:
  - Last statement is executed  
  - Or `exit()` system call is invoked  
- Parent may also terminate its children.  

---

# Interprocess Communication (IPC)
> Mechanisms for processes to exchange data and synchronize.

## Shared Memory
- Processes establish a shared memory region via a **system call**.  
- Requires **synchronization** to avoid race conditions.  
- Faster (direct memory access).  
- Example problem: **Producer–Consumer Problem**.  

## Message Passing
- More efficient for **small data** exchange.  
- Communication via **send/receive messages**.  

### Communication Methods
- **Sockets**: Network communication via IP & port (unstructured byte streams).  
- **Remote Procedure Calls (RPCs)**: Invoke functions across processes/machines.  

### Features
- Processes must establish a **communication link**.  
- Exchange messages via **send/receive** operations.  
- Supports different modes:  
  - **Direct** vs. **Indirect** (via mailbox/port)  
  - **Symmetric** vs. **Asymmetric**  
  - **Blocking (synchronous)** vs. **Non-blocking (asynchronous)**  

---
