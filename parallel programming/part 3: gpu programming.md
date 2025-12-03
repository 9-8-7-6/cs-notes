# GPU Programming

## Heterogrneous Computing

## CUDA Programming

### Kernel
A **Kernel** is a function that runs on the GPU and is executed by **many concurrent threads**.

#### 1. Execution Model
*   **Concept:** A Kernel represents "Many Concurrent Threads".
*   **Sequential vs Parallel:** Only **one kernel** is executed at a time on the device (historically), but **many threads** execute that kernel simultaneously.

#### 2. SIMT (Single Instruction, Multiple Threads)
*   Each thread executes the **same code** on **different data**.
*   Differentiation is achieved via the unique **`threadID`**.

#### 3. Thread Hierarchy
*   **Thread Types:**
    *   **Physical threads:** The actual hardware execution units.
    *   **Virtual threads:** Software abstraction (can exceed physical limits).
*   **Grouping:**
    *   Threads are grouped into **Thread Blocks**.
    *   A Kernel launch creates a **Grid** of thread blocks.

## GPU Architecture & Multi-GPU

## Optimization