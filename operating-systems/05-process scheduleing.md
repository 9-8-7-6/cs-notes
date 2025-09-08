# Process Scheduling
> Keep several multiprogramming in memory and rotate CPU among them.

---

## Basic Concepts
- **CPU burst**: Process execution consists of CPU computation time.  
- **I/O burst**: Process execution consists of I/O waiting time.  

---

## Preemptive vs. Non-Preemptive Scheduling

### Preemptive Scheduling
- CPU can be taken away from a running process.  
- Possible transitions:
  1. From **running → waiting** (I/O phase start)  
  2. From **running → ready** (time slice expired, time-sharing)  
  3. From **waiting → ready** (I/O phase finished)  
  4. Process termination  

- **Scheduler**: Decides which process gets CPU next.  
- **Dispatcher**: Performs context switch (loads process state, jumps to correct code).  
- **Note**: Requires process synchronization to avoid race conditions.

### Non-Preemptive Scheduling
- Once a process acquires CPU, it keeps it until:
  1. It voluntarily enters waiting state (I/O start).  
  2. It terminates.  

---

## Scheduling Criteria
1. **CPU utilization**  
   - Theoretically: 0% ~ 100%  
   - Real system: 40% ~ 90%  

2. **Throughput**  
   - Number of processes completed per unit time.  

3. **Turnaround time**  
   - Submission → Completion.  

4. **Waiting time**  
   - Total time spent in the *ready queue* (I/O waiting is **not** counted).  

5. **Response time**  
   - Submission → First response is produced (important in interactive systems).  

---

## Scheduling Algorithms (Software Level)

> Note: **I/O time is not counted as waiting time** when analyzing scheduling algorithms.

### 1. First-Come, First-Served (FCFS)
- **Definition**: Process that arrives first runs first.  
- **Pros**: Simple, fair in arrival order.  
- **Cons**:  
  - **Convoy effect**: Long process delays all shorter processes.  
  - High average waiting time.

---

### 2. Shortest Job First (SJF)
- **Definition**: Process with the shortest CPU burst runs first.  
- **Variants**:  
  1. **Non-preemptive** – Once a process starts, it runs to completion.  
  2. **Preemptive (Shortest Remaining Time First, SRTF)** – A new process with shorter burst time preempts.  

- **Challenge**: Need to predict CPU burst length (usually exponential averaging).  
- **Pros**: Theoretically minimizes average waiting time.  
- **Cons**:  
  - Burst length estimation is difficult.  
  - **Starvation** for long jobs.

---

### 3. Priority Scheduling
- **Definition**: Process with the highest priority runs first.  
- **Note**: All algorithms can be seen as priority scheduling with different priority definitions.  
- **Problem**: **Starvation** – low-priority jobs may never run.  
- **Solution**: **Aging** – gradually increase waiting processes’ priority.

---

### 4. Round-Robin (RR)
- **Definition**: Each process gets a fixed time quantum (TQ). When TQ expires, it is preempted and moved to the ready queue.  
- **Performance**:  
  - **Large TQ** → behaves like FCFS.  
  - **Small TQ** → responsive, but high context-switch overhead.  
- **Pros**:  
  - Fair, good for time-sharing systems.  
- **Cons**:  
  - Depends heavily on TQ selection.

---

### 5. Multilevel Queue Scheduling
- **Definition**: Processes are divided into multiple queues, each with its own scheduling policy.  
- **Rules**:  
  - Processes may move between queues (e.g., **aging**).  
  - Different queues serve different workloads:  
    - High-priority queues: interactive, I/O-bound jobs.  
    - Low-priority queues: CPU-bound jobs.  
- **Pros**: Tailored scheduling per workload type.  
- **Cons**: Complex, tuning needed to avoid starvation.

---

## Scheduling in Hardware Level

### Multi-Processor Scheduling
- **Asymmetric multiprocessing (AMP)**  
  - One master processor handles OS tasks; others run user processes.  

- **Symmetric multiprocessing (SMP)**  
  - Each processor is self-scheduling.  
  - Requires synchronization (locks, semaphores).

---

### Multi-Threaded / Multi-Core Systems
- Each core may support multiple hardware threads (e.g., Intel Hyper-Threading).  
- **Goal**: Reduce stalls by switching to another thread when waiting for memory.  

---

### Multi-Core Processor Scheduling
- **Memory stall**: CPU waits for data from memory.  
- **Coarse-grained multithreading**: Entire pipeline is switched when a stall occurs.  
- **Fine-grained multithreading**: Switch every cycle to maximize utilization.  

---

### Real-Time Scheduling
- **Definition**: Meeting process deadlines is crucial.  

- **Types**:  
  - **Soft real-time**: Missing deadline is tolerated but undesirable.  
  - **Hard real-time**: Missing deadline = total system failure.  

- **Algorithms**:  
  - FCFS  
  - **Rate-Monotonic (RM)** – Static priority, shorter period = higher priority.  
  - **Earliest Deadline First (EDF)** – Dynamic priority, process with closest deadline runs first.  

---

### Processor Affinity
- Binding processes to specific CPU cores.  
- **Benefits**: Better cache reuse.  
- **Types**:  
  - **Soft affinity**: OS may migrate process.  
  - **Hard affinity**: Process cannot migrate.  

---

### Memory Access Models
- **UMA (Uniform Memory Access)**  
  - All CPUs access memory with equal latency.  

- **NUMA (Non-Uniform Memory Access)**  
  - Memory latency depends on CPU-to-memory distance.  
  - Requires OS scheduling awareness.  

---

### Load Balancing
- **Goal**: Evenly distribute workload across CPUs.  
- **Methods**:  
  - **Push migration**: Overloaded CPU pushes tasks to idle ones.  
  - **Pull migration**: Idle CPU pulls tasks from busy ones.  
