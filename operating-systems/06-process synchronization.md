# Process Synchronization
> In **preemptive scheduling**, synchronization is required to ensure correct execution.

---

## Background
- **Concurrent access** to shared data may result in **data inconsistency**.  
- Need mechanisms to ensure **orderly execution** of cooperating processes.  

---

## Producer–Consumer Problem
- Classic example of process synchronization.  
- A **buffer** is shared between:
  - **Producer**: generates data and puts it into the buffer.  
  - **Consumer**: takes data from the buffer.  
- Buffer states:
  - **Empty** – consumer must wait.  
  - **Full** – producer must wait.  

![Producer-Consumer Model](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter5/5_00_ProducerConsumer.jpg)

### Issues
- The **counter** (tracking buffer slots) may need synchronization.  
- Because high-level code (e.g., `counter++`) compiles into **multiple machine instructions**, interleaving can occur:
  - Example: `LOAD → INC → STORE`.  
  - Without synchronization, two processes may overlap execution, causing wrong results.  

---

## Instruction Interleaving
- CPU executes instructions at a very fine granularity.  
- Context switches may happen **in the middle of an operation**.  
- Therefore, we cannot guarantee a critical section finishes without interruption.

---

## Race Condition
- **Definition**: The outcome of processes depends on the **timing** of their execution.  
- Happens when:
  1. Two or more processes access shared data.  
  2. At least one modifies the data.  
  3. Execution order is uncontrolled.  

- **Example**: Two threads incrementing a shared counter without locks → final value may be incorrect.  

- Commonly described as **critical section**

---

## Critical Section
> A protocol for processes to cooperate

- **N processes** compete to access shared data  
- **Critical section**: code segment where shared data is accessed  
- **Mutual exclusion**: no other process is allowed to execute in the critical section while one process is executing  
- Add **entry section** & **exit section** code to ensure mutual exclusion  

### Requirements
1. **Mutual Exclusion**: only one process in the critical section at a time  
2. **Progress**: if no process is in the critical section, the decision of who enters next cannot be postponed indefinitely  
3. **Bounded Waiting**: a process should not wait forever to enter its critical section  

![Critical section](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ8IpWRgnZza1LhqwYliAMfk-HjH7NT_9Yhvg&s)

---

## Algorithm for Two Processes

### Simple Turn-Based Algorithm
```c
int turn;   // turn = i → Pi can enter its critical section

/* Process 0 */
do {
    while (turn != 0)
        ; // busy wait
    // critical section
    turn = 1;
    // remainder section
} while (1);

/* Process 1 */
do {
    while (turn != 1)
        ; // busy wait
    // critical section
    turn = 0;
    // remainder section
} while (1);
```
Problem: Does not satisfy Progress requirement.

### Peterson's Solution

``` c
int turn;   // turn = i → Pi can enter its critical section
boolean flag[2];   // initially flag[0] = flag[1] = false
// flag[i] = true → Pi ready to enter its critical section

/* Process i */
do {
    flag[i] = TRUE;    // declare intent
    turn = j;          // give priority to the other process
    while (flag[j] && turn == j)
        ; // busy wait
    // critical section
    flag[i] = FALSE;   // withdraw intent
    // remainder section
} while (1);
```
#### Peterson's Solution guarantees:
- Mutual Exclusion
- Progress
- Bounded Waiting

---

## Pthreads Synchronization

### Mutex Locks
- Use `pthread_mutex_t` to protect **critical sections**.  
- Ensures that only **one thread** can access a shared resource at a time.  
- Prevents **race conditions**.  
- **Common functions**:
  - `pthread_mutex_init()` – initialize a mutex.  
  - `pthread_mutex_lock()` – acquire a lock (block if already locked).  
  - `pthread_mutex_unlock()` – release the lock.  
  - `pthread_mutex_destroy()` – free resources when done.  

### Condition Variables
- Used for **thread synchronization**, not just mutual exclusion.  
- Must be used **together with a mutex**.  
- Classic use case: **Producer–Consumer problem**.  
- Functions:
  - `pthread_cond_wait(&cond, &mutex)`  
    - Atomically releases the mutex and blocks the thread until signaled.  
  - `pthread_cond_signal(&cond)`  
    - Wakes up **one** waiting thread.  
  - `pthread_cond_broadcast(&cond)`  
    - Wakes up **all** waiting threads.  

### Hardware Support for Synchronization
At a lower level, hardware provides **atomic instructions** to implement synchronization primitives.  

- **Atomic**: the operation is indivisible and cannot be interrupted.  
- Common atomic operations:
  - **Test-and-Set (TAS)**
  - **Swap (Exchange)**  

#### Example: Test-and-Set
```c
boolean TestAndSet(boolean *lock) {
    boolean old = *lock;
    *lock = TRUE;
    return old;
}
```

- If lock was `FALSE`, the caller successfully acquires the lock.
- If lock was `TRUE`, another thread already holds it → caller must retry (busy waiting).

