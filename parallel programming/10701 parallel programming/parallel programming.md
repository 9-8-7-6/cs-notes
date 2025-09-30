# Parallel Programming

---

## What is Parallel Computing?
> Solve a single problem by using multiple processors (e.g., CPU cores, GPUs) working together.  

- Traditionally, programs were written for **serial computing**: one instruction at a time on a single processor.  
- Parallel computing allows tasks to be divided into smaller subtasks, executed **simultaneously** to improve performance.  

---

## Difference Between Parallel Computing & Distributed Computing

### Parallel Computing
- Runs a **single application** spread across multiple processors/cores.  
- Goal: **speed up execution** and handle larger computations.  
- Example: Using OpenMP to parallelize a matrix multiplication across 8 CPU cores.  

### Distributed Computing
- Runs activities across **multiple independent systems** or geographically separated servers.  
- Goal: **concurrency** and **resource sharing**, not only performance.  
- many machines cooperate, often focusing on **scalability and fault tolerance**.
- Example: Hadoop or Spark jobs spread across a cluster of machines.  

---
 