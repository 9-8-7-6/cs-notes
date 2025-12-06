# GPU Programming

**Core Concept:** A typical GPU can be thought of as being composed of one or more **SIMD** (Single Instruction, Multiple Data) processors.

---

## 1. GPU Architecture & Multi-GPU

### NVIDIA GPU Structure
*   **Streaming Multiprocessors (SMs):**
    *   NVIDIA GPUs are composed of multiple SMs.
    *   Each SM functions similarly to a SIMD processor.
*   **Streaming Processors (SPs) / CUDA Cores:**
    *   Each SM is composed of multiple SPs.
    *   These are the individual datapaths (cores) within an SM.
*   **SIMT (Single Instruction, Multiple Threads):**
    *   NVIDIA uses the term **SIMT** instead of SIMD to describe its specific execution model.

### Thread Level Scheduling - Warp
*   Software: grid -> blocks -> threads
*   Hardware: GPU(device) -> SM(multicore processor) -> core
*   Inside an SM, threads are launched in groups of 32 called warps. Threads in a warp execute the same instruction in parallel, while warps and blocks execute logically in parallel.

#### Thread group limits
*   Maximum execution concurrency
    *   Maximum number of resident grids per device: 32
    *   Maximum number of threads per multiprocessor: 2048
    *   Maximum number of threads per block: 1024

### Memory Hierarchy
*   **Local Memory**
*   **Shared Memory (Fast):**
    *   A small block of memory located inside each SM.
    *   Shared only among the internal SPs of that specific SM.
*   **Global Memory (Slow):**
    *   The large on-board memory (VRAM).
    *   Accessible by all SMs on the chip but has significantly higher latency compared to shared memory.

### Host vs. Device
*   **Host:** The CPU and its system memory (RAM).
*   **Device:** The GPU and its on-board memory (VRAM).

---

## 2. Heterogeneous Computing

> **Definition:** Writing a program that runs across different types of processors (e.g., CPU + GPU) is called **Heterogeneous Computing**.

*   **Concept:** The system consists of a **Host** (CPU) to manage execution and a **Device** (Accelerator) for heavy computation.
*   **Types of Accelerators:**
    *   **GPU** (Graphics Processing Units)
    *   **FPGA** (Field Programmable Gate Arrays)
    *   **DSP** (Digital Signal Processors)

---

## 3. CUDA Programming

### CUDA Programming Terminology
*   Host: CPU
*   Device: GPU
*   Kernel: functions executed on GPU
*   Thread: the basic execution unit
*   Block:  a group of threads
*   Grid: a group of blocks

### The Kernel
A **Kernel** is a function that runs on the GPU and is executed by **many concurrent threads**.

#### 1. Execution Model
*   **Concept:** A Kernel represents "Many Concurrent Threads".
*   **Sequential vs. Parallel:**
    *   Historically, only **one kernel** executes at a time on the device.
    *   However, **many threads** execute that single kernel simultaneously.
*   **Asynchronous Execution:**
    *   The CUDA kernel launch is **asynchronous**. The host function returns immediately after notifying the system to start the kernel.
    *   **Synchronization:** We need `cudaDeviceSynchronize()` to force the main function (Host) to wait until all executing kernels on the device are completed.

#### 2. SIMT (Single Instruction, Multiple Threads)
*   Each thread executes the **same code instructions**.
*   Each thread operates on **different data**.
*   Differentiation is achieved via a unique **`threadID`**.

#### 3. Thread Hierarchy
*   **Thread Types:**
    *   **Physical threads:** The actual hardware execution units.
    *   **Virtual threads:** Software abstraction (can exceed physical hardware limits).
*   **Grouping Structure:**
    1.  **Threads** are grouped into **Thread Blocks**.
    2.  A Kernel launch creates a **Grid** of thread blocks.
*   **Thread block** is a collection of threads run on a single SM.
*   kernelFunc<<<numBlocks, threadsPerBlock, sharedMemSize, streamID>>>(), numBlocks at the first value in angle brackets means number of thread blocks in the grid, the second value means the numbers of number of threads per block.
*   A grid is the collection of thread block started by a kernel.
*   **ThreadIdx**: the rank or index of the thread in its thread block.
*   **BlockDim**: the number of threads in a block (in x, y, z dimensions).

### Development Workflow
*   **API:** CUDA is the API for GPGPU (General-Purpose computing on Graphics Processing Units) programming.
*   **Dual-Code Structure:** A typical CUDA application requires writing two parts:
    1.  **Host Code:** Runs on the CPU.
    2.  **Device (Kernel) Code:** Runs on the GPU. It follows the **SPMD** (Single-Program Multiple-Data) model, where each thread runs a copy of the same code on its own data.
*   **Compilation:**
    *   CUDA programs cannot be compiled with an ordinary C compiler (like `gcc`).
    *   They require a specific **CUDA compiler (NVCC)** to generate machine language for both the host processor and the device processor.

---

## 4. Optimization