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

### Semaphores

- A **tool** to generalize the synchronization problem
- A record of how much resource are available
  - If #record = 1 -> binary semaphore
  - If #record > 1 -> counting semaphore   
- Use:
  - Wait: I need a resource
  - Signal: I need to free the resource because finishing

### Non-busy Waiting Implementation

#### 1. Core Idea
- **Semaphore**  
  - A synchronization data structure with:
    - An integer `value`
    - A queue `L` (holding blocked processes / PCBs)
  - Queue strategy can be FIFO, FILO, etc.

- **Purpose**  
  - Avoid busy waiting (CPU wasting cycles spinning).
  - Use **block() / wakeup()** system calls to suspend and resume processes efficiently.

---

#### 2. Workflow

##### Wait (P)

```c
void wait(semaphore S) {
  S.value--;
  if (S.value < 0) {
    add this process to S.L;
    sleep();   // block()
  }
}
```

##### Signal (V)

```c
void signal(semaphore S) {
  S.value++;
  if (S.value <= 0) {
    remove a process P from S.L;
    wakeup(P);
  }
}
```

---

#### Compare
- Busy waiting: wastes CPU, but good for short waits.
- Non-busy waiting: saves CPU, but system calls are slower → better for long waits.
---

#### Semaphore with Critical Section

##### `wait`

```c
void wait(semaphore S) {
  entry-section();
  S.value--;
  if (S.value < 0) {
    add this process to S.L;
    exit-section();
    sleep();   // block
  } else {
    exit-section();
  }
}
```

##### `signal`

```c
void signal(semaphore S) {
  entry-section();
  S.value++;
  if (S.value <= 0) {
    remove a process P from S.L;
    exit-section();
    wakeup(P);
  } else {
    exit-section();
  }
}
```

---

#### Cooperation Synchronization

- P1 execute S1; P2 execute S2
- S2 be executed only after S1 has completed

- Implementation:
``` c
//shared variable:
semaphore sync;  

P1:
  S1;
  signal(sync);

P2:
  wait(sync);
  S2;
```

---

### Classic Synchronization Problems

#### Bounded-Buffer (Producer-Consumer) Problem

- A pool of *n* buffers, each capable of holding one item
- Producer: grab an empty buffer and place one item into the buffer

- Consumer: grab a buffer and retract the item

---

#### Readers–Writers Problem (RW)

##### System Model
- **Shared Data Objects**: A set of common resources.  
- **Processes**:
  - **Reader processes**: Access data in read-only mode.
  - **Writer processes**: Modify data and require exclusive access.

##### rules
- Multiple **Readers** may access the shared data simultaneously.
- A **Writer** must have exclusive access (no other Readers or Writers allowed).

##### Priority Issues
1. First Readers–Writers Problem (Readers Priority): no reader will blocked waiting unless a writer is changing(updating) a shared object

``` c
// mutual exclusion for write
semaphore wrt = 1;
// mutual exclusion for readcount
semaphore mutex = 1;
int readcount = 0;

Writer() {
  while(TRUE) {
    wait(wrt);
    // Writer Code
    signal(wrt);
  }
}

Reader() {
  while(TRUE) {
    wait(mutex);
      readcount++;
      if(readcount == 1)  // It Means First Reader
        wait(wrt);
    signal(mutex);
    // It Means Not First Reader(Having Permission)
    // Reader Code
    wait(mutex);
      readcount--;
      if(readcount==0)  // Release write lock if no more reads
        signal(wrt);
    signal(mutex);
  }
}
```
###### Notes
- Readers share a single wrt lock
- Writer may have starvation problem

2. Second Readers–Writers Problem (Writers Priority)
**Rule**: Once any writer is ready, **no new reader may start**; writers get priority.  
**Idea**: Use a *gate* (`readTry`) that writers can close while they wait, so **new readers are held back**. Readers already inside may finish.

###### Semaphores & Counters
- `resource` = 1 — mutual exclusion for the shared object (writer or first/last reader).
- `readTry` = 1 — *gate* that writers can hold to block **new** readers.
- `rmutex` = 1 — protects `readcount`.
- `wmutex` = 1 — protects `writecount`.
- `readcount`, `writecount` — number of active readers / waiting+active writers.


```c
semaphore resource = 1;  // lock for the shared resource (lock by writers or first/last reader)
semaphore readTry  = 1;  // gate readers pass through; writers hold to block new readers
semaphore rmutex   = 1;  // protects readcount from many readers change to race condition
semaphore wmutex   = 1;  // protects writecount from many writers change to race condition
int readcount  = 0;   // Numbers of readers reading
int writecount = 0;   // Bynbers of writers waiting or writing

// --- writer has priority ---
Writer() {
  while (TRUE) {
    // First writer closes the gate to block new readers
    wait(wmutex);
      writecount++;
      if (writecount == 1)      // first waiting/active writer
        wait(readTry);          // close the gate so new readers can't start
    signal(wmutex);

    // Exclusive access to the shared resource
    wait(resource);
      // --- write critical section ---
      // ... Writer Code ...
    signal(resource);

    // Writer done; last writer reopens the gate for readers
    wait(wmutex);
      writecount--;
      if (writecount == 0)      // last writer done
        signal(readTry);        // reopen the gate for readers
    signal(wmutex);
  }
}

Reader() {
  while (TRUE) {
    // Try to pass the gate; if a writer is/gets ready, gate blocks new readers
    wait(readTry);              // briefly acquire the gate
      wait(rmutex);
        readcount++;
        if (readcount == 1)     // first reader locks the resource
          wait(resource);
      signal(rmutex);
    signal(readTry);            // release gate quickly so writers can grab it

    // --- read critical section ---
    // ... Reader Code ...

    // Reader exit; last reader releases the resource
    wait(rmutex);
      readcount--;
      if (readcount == 0)
        signal(resource);
    signal(rmutex);
  }
}
```

###### Notes
- Starvation: Readers can be delayed if writers arrive continuously.
- Correctness roles:
  - `resource`: exclusivity for writer or the first/last reader pair.
  - `readTry`: writer-controlled gate to block new readers.
  - `rmutex` / `wmutex`: protect the respective counters.

---

#### Dining-Philosopher Problem
- Chopsticks are resources as semaphore.
- Each process need resources.
