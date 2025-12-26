# GPU Programming

**Core Concept:** A typical GPU can be thought of as being composed of one or more **SIMD** (Single Instruction, Multiple Data) processors.

---

## 1. GPU Architecture & Multi-GPU

### GPU
*   A specialized chip designed for rapidly display and visualization.
*   Massively multithreaded manycore chips.

### GPGPU(General-Purpose Graphic Processing Unit)
*   Exploit data parallelism for solving embarrassingly parallel tasks and numeric computations.
*   Programmable:
    *   Early GPGPU: using libraries in computer graphic, e.g. OpenGL or DirectX.
    *   Now CUDA and openCL provides an extension to C and C++ enable parallel programming on GPUs.

### NVLink
*   Data transfor between GPUs.

### NVIDIA GPU Structure
*   **Streaming Multiprocessors (SMs):**
    *   NVIDIA GPUs are composed of multiple SMs.
    *   Each SM is a vector machine, and functions similarly to a SIMD processor.
    *   Shared register files.
*   **Streaming Processors (SPs) / CUDA Cores:**
    *   Each SM is composed of multiple SPs.
    *   These are the individual datapaths (cores) within an SM.
*   **SIMT (Single Instruction, Multiple Threads):**
    *   NVIDIA uses the term **SIMT** instead of SIMD to describe its specific execution model.

### Thread Level Scheduling - Warp
*   Software: threads -> blocks -> grid
*   Hardware: core -> SM(multicore processor) -> GPU(device)
*   Inside an SM, threads are launched in groups of 32 called warps. Threads in a warp execute the same instruction in parallel, while warps and blocks execute logically in parallel.

#### Thread group limits
*   Maximum execution concurrency
    *   Maximum number of resident grids per device: 32
    *   Maximum number of threads per multiprocessor: 2048
    *   Maximum number of threads per block: 1024

### Memory Hierarchy
*   Registers
    *   Automatic variables(scalar/array) inside kernels.
    *   Data lifetime = thread lifetime.
    *   Accessible by any thread in the threadblock.

*   **Per-thread Local Memory**
*   **Per-block- Shared Memory(Fast):**
    *   A small block of memory located inside each SM.
    *   Shared only among the internal SPs of that specific SM.
    *   C/C++: **__shared__** int a[SIZE];
    *   Date lifetime = block lifetime.
*   **Global Memory (Slow):**
    *   The large on-board memory (VRAM).
    *   Accessible by all SMs on the chip but has significantly higher latency compared to shared memory.

### Host vs. Device
*   **Host:** The CPU and its system memory (RAM).
*   **Device:** The GPU and its on-board memory (VRAM).

---

## 2. Heterogeneous Computing

> **Definition:** An integrated computing model or system consists of different types of processors/computing unit (e.g., GPU, DSP, FPGA, ASIC, Co-processor).

*   **Concept:** The system consists of a **Host** (CPU) to manage execution and a **Device** (Accelerator) for heavy computation.This model applies to CUDA/OpenCL systems. HSA systems do not use the Host–Device separation.
*   **Types of Accelerators:**
    *   **GPU** (Graphics Processing Units)
    *   **FPGA** (Field Programmable Gate Arrays)
    *   **DSP** (Digital Signal Processors)
*   **Types of Architecture:**
    *   GPU Servers: CPU communicates with GPU through PCIe/NVLink and requires memory copies between CPU memory and GPU memory, which often becomes a bottleneck.
    *   Heterogeneous System Architecture(HSA): 
        *   HSA provides hardware-managed unified memory, reducing the need for OS-mediated memory copies.
        *   Unified coherent memory.
        *   CPU and GPU integrated on a single chip.
        *   Example: AMD APU (Accelerated Processing Unit), originally marketed under the Fusion branding.

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
*   Each thread operates on **different data** based on its threadID.
*   Differentiation is achieved via a unique **`threadID`**.

#### 3. Thread Hierarchy
*   **Thread Types:**
    *   **Physical threads:** The actual hardware execution units and context switching are essentially free.
    *   **Virtual threads:** Software abstraction (can exceed physical hardware limits).
*   **Grouping Structure:**
    1.  **Threads** are grouped into **Thread Blocks**.
    2.  A Kernel launch creates a **Grid** of thread blocks.
*   **Thread block** is a collection of threads run on a single SM.
*   kernelFunc<<<numBlocks, threadsPerBlock, sharedMemSize, streamID>>>(), numBlocks at the first value in angle brackets means number of thread blocks in the grid, the second value means the numbers of number of threads per block.
*   A grid is the collection of thread block started by a kernel.
*   **ThreadIdx.[x y z]**: the rank or index of the thread in its thread block.
*   **BlockIdx.[x y z]**: block index within the grid.
*   **BlockDim.[x y z]**: the number of threads in each block.
*   **GridDim.[x y z]**: the number of blocks in each grid.
*   **Index = threadIdx.x + blockIdx.x * blockDim.x**
*   The index of threads and blocks can be denoted by a 3 dimensional struct, dim3 defined in vector_types.h, struct dim3 {x; y; z;};

#### 4. Function Qualifiers

*   __device__ : executed on the device, callable from the device only
*   __global__ : executed on the device, callable from the host only
*   __host__ : executed on the host, callable from the host only
*   __host__device__ : compiled for both the host and the device.

#### 5. Variable Type Qualifiers

*   __device__ : resides in device's global memory space
*   __constant__ : has the lifetime of an application is accessible from all the threads within the grid and from the host through the runtime library
*   __shared__ : resides in the shared memory space of a thread block, has the lifetime of the block

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
