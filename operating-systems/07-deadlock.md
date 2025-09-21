# Deadlock

> **Definition**  
> A deadlock is a set of blocked processes, each holding at least one resource and waiting to acquire another resource held by another process in the set.

---

## Necessary Conditions (Coffman Conditions)

1. **Mutual Exclusion**  
   - Only one process can use a resource at a time.  

2. **Hold and Wait**  
   - A process holding some resources is waiting to acquire additional resources.  

3. **No Preemption**  
   - A resource can only be released voluntarily by the process holding it.  

4. **Circular Wait**  
   - There exists a set of processes {P0, P1, …, Pn} such that:
     - P0 is waiting for a resource held by P1  
     - P1 is waiting for a resource held by P2  
     - Pn is waiting for a resource held by P0  

---

## System Model

- **Resource types**: R1, R2, …, Rn  
- **Resources** include CPU, memory, I/O devices, files, etc.  
- Each resource type **Ri** may have **Wi** instances.  
- Resource usage follows: Request → Use → Release

---

## Resource-Allocation Graph (RAG)

- **Vertices**:  
- Processes (circles)  
- Resources (squares)  

- **Edges**:  
1. **Request edge**: `P → R`  
   - Process P requests resource R.  
2. **Assignment edge**: `R → P`  
   - Resource R is assigned to process P.  

- **Cycle detection**:  
- If the graph contains **no cycle** → No deadlock.  
- If the graph contains a **cycle**:  
  - **Single instance per resource type** → Deadlock exists.  
  - **Multiple instances per resource type** → Deadlock *may* exist.  

---

## Handling Deadlocks

### 1. Prevention & Avoidance (Never Enter Deadlock)
- **Prevention**: Ensure at least one of the four necessary conditions is not satisfied.  
- **Avoidance**: Dynamically examine resource-allocation state before allocation (e.g., Banker’s Algorithm).  

### 2. Detection & Recovery (Allow Deadlock, then Resolve)
- **Detection**: Periodically check if deadlock exists (e.g., Wait-for Graph).  
- **Recovery**: Abort processes or preempt resources.  

### 3. Ignore the Problem
- Pretend deadlocks never occur.  
- This is the approach used by many general-purpose operating systems (e.g., UNIX, Linux, Windows).  

---

## Deadlock Prevention — Breaking the Conditions

1. **Mutual Exclusion**  
 - Not required for shareable resources (e.g., read-only files).  
 - Non-shareable resources (e.g., printers) must still enforce mutual exclusion.  

2. **Hold and Wait**  
 - Require processes to request all resources at once, or release all held resources before requesting new ones.  
 - **Disadvantage**: Low resource utilization; possible starvation.  

3. **No Preemption**  
 - If a process requests a resource that cannot be immediately allocated, preempt all resources it currently holds.  
 - Example: CPU preemption during context switch.  

4. **Circular Wait**  
 - Impose a **total ordering** of all resource types.  
 - Processes must request resources in increasing order, preventing cycles.  

---

## Deadlock Avoidance

- **Safe state**:  
A system is in a safe state if there exists a sequence of allocations that can satisfy the requests of all processes.  

- **Implications**:  
- Safe state → **No deadlock**  
- Unsafe state → **Possibility of deadlock**  
- Deadlock avoidance ensures the system never enters an unsafe state.  

---

### 1. Single Instance of Each Resource Type
- **Resource-Allocation Graph (RAG) Algorithm**  
- Based on cycle detection.  

#### Edge Types
1. **Request edge**: `Pi → Rj`  
 - Process `Pi` requests (is waiting for) resource `Rj`.  
2. **Assignment edge**: `Rj → Pi`  
 - Resource `Rj` is currently assigned to process `Pi`.  
3. **Claim edge**: `Pi → Rj` (dashed edge)  
 - Process `Pi` **may request** `Rj` in the future.  
 - A claim edge becomes a request edge when `Pi` requests the resource.  
 - An assignment edge reverts to a claim edge when the resource is released.  

> Run a **cycle-detection algorithm** whenever a claim edge becomes an assignment edge.  

---

### 2. Multiple Instances of Each Resource Type
- **Banker’s Algorithm**  
- Based on **safe sequence detection**.  
- A request is granted **only if** the resulting allocation leaves the system in a safe state.  
- Suitable for **multiple instances** of each resource type.  

#### Safety Algorithm (Steps)
1. Assume each process may need up to its *maximum declared resources*.  
2. Find a process whose remaining need ≤ currently available resources.  
3. Pretend that process finishes, release its allocated resources back to the pool.  
4. Repeat step 2 until:  
 - All processes can finish → **Safe state**.  
 - No such process can be found → **Unsafe state**.  

---

## Deadlock Detection

- **Single instance** of each resource type  
- Convert request/assignment edges into a **wait-for graph**.  
- Deadlock exists if the graph contains a cycle.  

- **Multiple instances** of each resource type  
- Use safety algorithm to check if the system is in a safe state.  

---

## Deadlock Recovery

1. **Process termination**  
 - Abort all deadlocked processes.  
 - Abort one process at a time until the deadlock cycle is eliminated.  

2. **Resource preemption**  
 - Select a victim process and preempt its resources.  
 - Rollback the process (partially or entirely).  
 - Beware of starvation (avoid repeatedly preempting the same process).  
