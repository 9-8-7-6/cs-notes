# Process Concept
  
## Process Concept
### Program vs. Process
- **Program** - *passive*:binary stored in disk
- **Process** - *active*:program executed in memory

![Process Concept Diagram](https://cdn-images-1.medium.com/max/900/1*6vsoP1cWzQkN95AlEt2WoA.jpeg)
 
### Components of a Process
- Code Segment(text section)
- Data Section(global variables)
- Stack(temporary local variable and function)
- Heap (dynamically allocated memory such as malloc / new objects)
- Program counter(register to store the address of next instruction to execute)
- A set of associated resource(e.g open file handler)

### Threads(A.k.a lightweight process)
- Thread and process management are similar, so this chapter focuses mainly on processes
- Basic unit of CPU utilization
- All threads belong to the same process share(code section, data section, OS resources)

### Process State(Virtual Concept)
![Process State Diagram](https://i.imgur.com/vD7tDw5.png)
- New:The process is being created(that is program loaded in memory and not yet ready to run, but not always fully loaded yet)
- Ready:The process is in the memory waiting queue to be assigned to processor(CPU)
- Running:Instructions are being executed by CPU
- Waiting:Process is waiting for an event to complete (e.g., I/O operation)
- Terminated:The process has finished, free the memory

### Process Control Block(PCB)
![Process Control Block](https://cdn1.byjus.com/wp-content/uploads/2022/06/process-control-block.png)

- stores the current [Process State](#process-statevirtual-concept)
- The OS creates a PCB entry for each new process.
- feature: Store process information in memory

### Context Switch
- Switch process executed by CPU
- Occur when interrupt or system call(e.g mouse or keyboard) happen 
- That is store the state of process into process control block and load the saved state of new process


## Process Scheduling
- Multiprogramming: running several programs at the same time to use the computer more efficiently
- Time Sharing:context switch frequently such that user can **interact** with computer

### Process Schedule Queues
> Processes migrate between various queues

- Job queue(New State)
- Ready queue(Ready State)
- Device queue(Wait State)

### Schedulers
- Short-term scheduler(CPU scheduler):*frequently* Memory to CPU(Ready State -> Run State)
- Long-term scheduler(job scheduler):Disk to Memory(New State -> Ready State)
- Medium-term scheduler:
    - swap out: Memory to Disk(Ready State -> Wait State), removing processes from memory to reduce the degree of multiprogramming, **Virtual Memory** related
    - swap in: reintroducing swap-out processes into memory

![Schedulers](https://afteracademy.com/images/what-is-longterm-shortterm-and-mediumterm-scheduler-longterm-shortterm-working.png)

## Operations on Processes

### Tree of Processes
- Each process is identified by a unique processor identifier(pid), and is in tree structure(parent and children relation)

### Resource Creation
- Resource sharing
    - Parent and child processes share all resources
    - Child process share *subset* of parent's resources
    - Parent and child process share *no* resources
- Memory content
    - Child duplicate of parent
    - Child has a program loaded into it 
- UNIX/Linux Process Creation
    - *Fork* system call
        - Create a duplicated of its parent
        - Child & Parent execute concurrently
        - Childs return a value 0, Parents return PID
    - *Execlp* system call
        - Load new binary code into memory 
    - *Wait* system call
        - Parent waits for one of its child process to complete
- Process Termination
    - Terminate when the last statement is executed or exit() is called
    - Parent may terminate children
## Interprocess Communication(IPC)
> a set of methods for exchanging data among multiple threads in one or more processes

- Shared memory
    - Require more careful user *synchronization*, and make sure data are not written simultaneously by processes
    - Faster speed by memory address access
    - Processes create a region of shared memory by system call and attach to os
    - Consumer & Producer Problem:

- Message passing
    - more efficient for *small* data
    - Send/Receive message
    - Communication Methods
        - Sockets: network connection by IP & Port, exchange unstructured stream of bytes
        - Remote Procedure Calls: Call another process or computer's function
    - Mechanism for processes to communicate and synchronize their actions
    - Need to establish a communication link
    - Exchange a message by send/receive 
    - Direct / Indirect communication
        - Direct: need to name the target to send or receive, One-to-One relation
        - Indirect: Messages are from mailboxes(alse as ports)
    - Symmetric / Assymmetric communication
    - Blocking / Non-blocking
        - blocking(synchronous)
        - non-blocking(asynchronous)