# GPU Programming

**Core Concept:** A typical GPU can be thought of as being composed of one or more **SIMD** (Single Instruction, Multiple Data) processors.

---

## 1. GPU Architecture & Multi-GPU

### NVIDIA GPU Structure
*   **Streaming Multiprocessors (SMs):**
    *   NVIDIA GPUs are composed of multiple SMs.
    *   Each SM functions similarly to a SIMD processor.
*   **Streaming Processors (SPs) / CUDA Cores:**
    *   These are the individual datapaths (cores) within an SM.
*   **SIMT (Single Instruction, Multiple Threads):**
    *   NVIDIA uses the term **SIMT** instead of SIMD to describe its specific execution model.

### Memory Hierarchy
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

### The Kernel
A **Kernel** is a function that runs on the GPU and is executed by **many concurrent threads**.

#### 1. Execution Model
*   **Concept:** A Kernel represents "Many Concurrent Threads".
*   **Sequential vs. Parallel:**
    *   Historically, only **one kernel** executes at a time on the device.
    *   However, **many threads** execute that single kernel simultaneously.

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

    $ \text{Grid} \supset \text{Thread Blocks} \supset \text{Threads} $

### Development Workflow
*   **API:** CUDA is the API for GPGPU (General-Purpose computing on Graphics Processing Units) programming.
*   **Dual-Code Structure:** A typical CUDA application requires writing two parts:
    1.  **Host Code:** Runs on the CPU.
    2.  **Device Code:** Runs on the GPU (Kernels).
*   **Compilation:**
    *   CUDA programs cannot be compiled with an ordinary C compiler (like `gcc`).
    *   They require a specific **CUDA compiler (NVCC)** to generate machine language for both the host processor and the device processor.

---

## 4. Optimization