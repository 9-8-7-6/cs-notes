# GPU Programming

**Core Concept:** A typical GPU can be thought of as being composed of one or more **SIMD** (Single Instruction, Multiple Data) processors.

---

## 1. GPU Architecture & Multi-GPU

### GPU
*   A specialized chip designed for rapid display and visualization.
*   Massively multithreaded manycore chips.

### GPGPU(General-Purpose Graphics Processing Unit)
*   Exploit data parallelism for solving embarrassingly parallel tasks and numeric computations.
*   Programmable:
    *   Early GPGPU: using libraries in computer graphic, e.g. OpenGL or DirectX.
    *   Now CUDA and OpenCL provides an extension to C and C++ enable parallel programming on GPUs.

### NVLink
*   Data transfer between GPUs.

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
*   Inside an SM, threads are launched in groups of 32 called warps. Threads in a warp execute the same instruction physically in parallel, while warps and blocks execute logically in parallel.
*   Warps are switched when memory stalls.
*   Warp Divergence : can't execute the same instruction in the same cycle in the warp
    *   Occurs when threads within the same warp follow different execution paths due to control-flow instructions(e.g., if, else, switch) with thread-dependent branch conditions.
    *   Warp divergence does not affect different warps; it only impacts threads within the same warp.

```c
__global__ void per_thread_sum
(int *indices, float *data, float *sums) {
    ...
    // number of loop iterations per thread is data dependent
    // This kernel exhibits warp divergence due to data-dependent loop bounds, causing different threads in the same warp to execute a different number of iterations.
    int i = threadIdx.x;
    for (int j = indices[i]; j < indices[i+1]; j++) {
        sum += data[j];
    }
    sums[i] = sum;
}
```

### Unroll the for-loop

*   Unroll the statements can reduce the branches and increase the pipeline.

```c
for (i = 0; i < n; i++) {
    a = a + i;
}

// Unrolled 3 times
for (i = 0; i < n; i += 3) {
    a = a + i;
    a = a + i + 1;
    a = a + i + 2;
}
```

*   #pragma unroll
```c
#pragma unroll 5
for (int i = 0; i < n; i++)
// the loop will be unrolled 5 times
```

#### Thread group limits
*   Maximum execution concurrency
    *   Maximum number of resident grids per device: 32
    *   Maximum number of threads per multiprocessor: 2048
    *   Maximum number of threads per block: 1024

### Memory Hierarchy
*   Registers
    *   Scalar variables declared inside kernels.
    *   Fastest on-chip storage.
    *   Data lifetime = thread lifetime.
    *   Accessible only by the owning thread.

*   **Per-thread Local Memory**
    *   Per-thread private memory
    *   Used when registers spill or for large arrays.
*   **Per-block Shared Memory(Fast):**
    *   Shared variables.
    *   On-chip memory located inside each SM.
    *   Shared among threads within the same block.
    *   C/C++: **__shared__** int a[SIZE];
    *   Data lifetime = block lifetime.
*   **Global Memory (Slow):**
    *   Global memory / Constant memory
    *   The large on-board memory (VRAM).
    *   Accessible by all SMs on the chip but has significantly higher latency compared to shared memory.

### Host vs. Device
*   **Host:** The CPU and its system memory (RAM).
*   **Device:** The GPU and its on-board memory (VRAM).

#### Limit of Dynamic Allocation

*   if you have multiple extern declaration of shared, extern __shared__ float As[], extern __shared__ float Bs[], both of As, Bs point to the same address.
*   Solution: Keep As and Bs inside the 1D-array, extern __shared__ float smem[], when indexing elements in As (smem[0:sAs-1]), Bs (smem[sAs:sAs+sBs]).

---

#### Static Shared Memory Allocation

*   If the size of shared memory is know in compilation time, shared memory can be allocated statically.

```c
__global__ void FW_APSP(int k, int D[][]) {
    __shared__ int DS[10*10];
    ...
}
```

#### Constant memory

*   Read only
*   Declare by variable qualifier __constant__
*   Each SM has its own constant memory

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
*   kernelFunc<<<numBlocks, threadsPerBlock, sharedMemSize, streamID>>>();, numBlocks at the first value in angle brackets means number of thread blocks in the grid, the second value means the number of threads per block.
*   A grid is the collection of thread block started by a kernel.
*   **ThreadIdx.[x y z]**: the rank or index of the thread in its thread block.
*   **BlockIdx.[x y z]**: block index within the grid.
*   **BlockDim.[x y z]**: the number of threads in each block.
*   **GridDim.[x y z]**: the number of blocks in each grid.
*   **Index = threadIdx.x + blockIdx.x * blockDim.x**
*   The index of threads and blocks can be denoted by a 3-dimensional struct, dim3 defined in vector_types.h, struct dim3 {x; y; z;};

#### 4. Function Qualifiers

*   __device__ : executed on the device, callable from the device only
*   __global__ : executed on the device, callable from the host only
*   __host__ : executed on the host, callable from the host only
*   __host__device__ : compiled for both the host and the device.

#### 5. Variable Type Qualifiers

*   __device__ : resides in device's global memory space
*   __constant__ : has the lifetime of an application is accessible from all the threads within the grid and from the host through the runtime library
*   __shared__ : resides in the shared memory space of a thread block, has the lifetime of the block

#### 6. Program Compilation

*   Source files containing CUDA device code must be compiled via nvcc, NVCC separates host code and device code, compiling host code with a standard C/C++ compiler and device code through the CUDA compilation pipeline.
Device code is typically compiled in two stages: first to PTX (a virtual ISA), and then to device-specific binary code (SASS).

### Development Workflow
*   **API:** CUDA is the API for GPGPU (General-Purpose computing on Graphics Processing Units) programming.
*   **Dual-Code Structure:** A typical CUDA application requires writing two parts:
    1.  **Host Code:** Runs on the CPU.
    2.  **Device (Kernel) Code:** Runs on the GPU. It follows the **SPMD** (Single-Program Multiple-Data) model, where each thread runs a copy of the same code on its own data.
*   **Compilation:**
    *   CUDA programs cannot be compiled with an ordinary C compiler (like `gcc`).
    *   They require a specific **CUDA compiler (NVCC)** to generate machine language for both the host processor and the device processor.

---

### CPU & GPU Synchronization

*   Most CUDA function calls are asynchronous.Control is returned to the host thread before the device has completed the request.
*   Kernel launch, asynchronous memory copy and set options, cudaMemcpy within the same device, H2D cudaMemcpy of 64kB or less, cudaEvent functions.
*   Programmer must enforce synchronization between GPU and CPU when data-dependent.

#### Synchronization Mechanisms
*   Device based: **cudaDeviceSynchronize()** which blocks a CPU thread until all issued CUDA calls to a device complete.
*   Context based: **cudaThreadSynchronize() (deprecated, use cudaDeviceSynchronize)** which block a CPU thread until all issued CUDA calls from the thread complete.
*   Stream based: **cudaStreamSynchronize(stream-id)**, block a CPU thread until all CUDA calls in stream stream-id complete.
*   Event based: **cudaEventSynchronize (event)**,block a CPU thread until event is recorded, **cudaStreamWaitEvent(stream-id, event)**, block a GPU stream until event reports completion.

#### CUDA event
CUDA events are lightweight primitives used for synchronization and timing.
*   Data type : cudaEvent_t
*   Common event APIs :  cudaEventCreate(&event) , cudaEventRecord(event, stream) , cudaEventSynchronize(event) , cudaEventElapsedTime(&ms, start, end) , cudaEventDestroy(event)
*   Error handling : cudaError_t, which should be checked to ensure correct execution.

### Multi-GPUs

*   Multiple CPU threads belonging to the same process

#### Sharing data between GPUs

*   Explicit copies via host : device A to host, host to device B
*   Zero-copy shared host array : direct device access to host memory over PCI-e in lower bandwidth and higher latency than GPU global memory.With using cudaMemcpy, but the host memory must be pinned(page-locked) to in case pageable memory cannot be directly accessed by the GPU due to OS virtual memory mechanism.
    *   cudaHostAlloc() : allocate pinned(page-locked) host memory for higher cudaMemcpy performance, and use with cudaMemAsync() for asynchronous memory copy or CUDA stream.
    *   cudaMallocHost() : add the flag cudaHostAllocMapped to allocate pinned host memory or cudaHostAllocPortable to allocate shared host memory.
*   Peer-to-peer memory copy : direct copy from pointer on GPU A to pointer on GPU B.

---

### Dynamic parallelism

The ability to launch new grids from the GPU dynamically / simultaneously / independently and dynamic parallelism allows a CUDA kernel to launch other kernels directly on the GPU, without returning control to the CPU.

Benefits:
*   Move host-side control loops with dynamic or irregular workloads to the GPU.
*   Run dynamically generated independent tasks on the GPU.
*   Reduce CPU–GPU synchronization and host-side launch overhead

Use cases:
*   Dynamic block and grid size determination
*   Dynamic work generation
*   Nested Parallelism

---

## 4. Optimization

