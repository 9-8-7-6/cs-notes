# Process Scheduling
> Keep several multiprogramming in memory and rotation

* CPU burst(Process execution consists of CPU wait)
* I/O burst(I/O execution consists of CPU wait)

---

## Preemptive vs. Non-preemptive
* Preemptive scheduling:
  1. From running to waiting state(I/O phase start)
  2. `From running to ready state(time sharing)`
  3. `From waiting to read state(I/O phase finish)`
  4. Terminate
Require process synchronization(CPU burst only, not I/O)

**Scheler**: make decision
**Dispatcher**: do switch

* Non-preemptive scheduling:
  1. From running to waiting state(I/O phase start)
  2. Terminate

---

## Scheduling Criteria
* CPU utilization
  * Thoretically: 0%~100%
  * Real system: 40%~90%

* Throughput
  * Number of completed processes per time unit

* Turnaround time
  * submission ~ completion

* Waiting time
  * total waiting time in the *ready queue*

* Response time
  * submission ~ first response is produced

---

## Algorithm (Software Level)

> Note: **I/O time is not counted in waiting time** when analyzing scheduling algorithms.

---

### 1. First-Come, First-Serve (FCFS) Scheduling
- **Definition**: The process that arrives first gets the CPU first.  
- **Pros**: Simple and fair in terms of arrival order.  
- **Cons**:  
  - **Convoy effect**: A long process at the front delays all shorter ones.  
  - Average waiting time can be very high.

---

### 2. Shortest-Job-First (SJF) Scheduling
- **Definition**: The process with the shortest CPU burst length gets the CPU first.  
- **Types**:  
  1. **Non-preemptive** – Once a process gets the CPU, it cannot be preempted until completion.  
  2. **Preemptive (Shortest Remaining Time First, SRTF)** – A new process with a shorter burst time can preempt the CPU.  
- **Challenge**: The exact length of the next CPU burst is unknown, so the system estimates using past behavior (approximate SJF).  
- **Pros**:  
  - Optimal for minimizing average waiting time (theoretically).  
- **Cons**:  
  - Requires burst time prediction.  
  - Can cause **starvation** for long processes.

---

### Priority Scheduling
- **Definition**: CPU is allocated to the process with the highest priority.  
- **Note**: All scheduling algorithms can be seen as priority scheduling, but the definition of priority differs (arrival time, burst length, etc.).  
- **Problem**: **Starvation** – low-priority processes may never execute.  
- **Solution**: **Aging** – gradually increase the priority of waiting processes over time.

---

### 3. Round-Robin (RR) Scheduling
- **Definition**: Each process gets a small, fixed time quantum (TQ). When TQ expires, the process is preempted and placed back into the ready queue.  
- **Performance**:  
  - If **TQ is large** → Behavior approaches **FIFO**.  
  - If **TQ is small** → Better responsiveness, but **context-switch overhead increases**.  
- **Pros**:  
  - Fair to all processes.  
  - Good for time-sharing systems.  
- **Cons**:  
  - Performance depends heavily on the choice of TQ.

---

### 4. Multilevel Queue Scheduling
- **Definition**: Processes are divided into different queues, each with its own scheduling algorithm.  
- **Rules**:  
  - Processes can move between queues (e.g., through **aging**).  
  - Different queues serve different types of processes:  
    - **High-priority queues**: Interactive and I/O-bound processes (short CPU bursts).  
    - **Low-priority queues**: CPU-bound processes (long CPU bursts).  
- **Pros**:  
  - Can tailor scheduling policies to different types of workloads.  
- **Cons**:  
  - More complex.  
  - Requires careful tuning to avoid starvation.
