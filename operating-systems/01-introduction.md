# Lecture 01: Introduction to Operating Systems

## I/O Communication Basics

- There is a **passive controller** between the device and memory to handle communication, due to the large speed difference between them.
- The **CPU issues commands**, after which **data is transferred** to the **controller's buffer**, and then written back to memory.

## Legacy I/O Mechanism: Busy Waiting

- In older systems, the CPU would **continuously poll the device** to check whether I/O was available.
- This approach is known as **busy waiting**, which is inefficient as it wastes CPU cycles.

## Modern I/O Mechanism: Interrupt-Driven Architecture

- Modern systems adopt an **event-driven architecture**.
- A device sends an **interrupt** to notify the CPU when it is ready.
- The CPU **pauses its current task**, handles the interrupt through an **interrupt service routine (ISR)**, and then **resumes the interrupted task**.

## Types of Interrupts

Interrupts can be classified into two main types:

### Hardware Interrupts

- Triggered by external hardware devices (e.g., keyboard, disk, network interface).
- Also referred to as **signals** in hardware contexts.
- Commonly used for asynchronous notifications to the CPU.

### Software Interrupts

- Triggered intentionally by programs during execution.
- Common cases include:
  - **Errors**, such as division by zero or illegal memory access.
  - **System calls**, where a program requests a service from the operating system.
- Software interrupts are also called **traps**.

## How Software Interrupts Work

- A software interrupt is intentionally triggered by a running program, either due to:
  - A **runtime error** (e.g., divide by zero, invalid memory access), or
  - A **system call** (a request for an OS-level service).

- When a software interrupt occurs:
  1. The CPU receives the **interrupt instruction** (e.g., `int` in x86 assembly).
  2. A specific **interrupt number** is encoded in the instruction to identify the requested service or exception type.
  3. The CPU uses this interrupt number to index into the **interrupt vector table** and locate the corresponding **trap handler** or **system call handler**.
  4. The CPU **saves the current context**, including the program counter (PC) and relevant registers.
  5. It **switches to kernel mode** to ensure privileged execution of the handler.
  6. The **interrupt service routine (ISR)** or **trap handler** is executed to perform the required action.
  7. After completing the routine, the CPU **restores the saved context** and **returns to user mode**, resuming execution from the point of interruption or based on return value.

> Note: Unlike hardware interrupts (which are asynchronous), software interrupts are **synchronous**, since they are triggered by the current instruction stream.

# Hardware Protection

Modern operating systems rely on hardware support to enforce protection between user programs and system resources. This ensures stability, security, and isolation.

## Dual Mode Operation

- The OS must ensure that **incorrect or malicious programs** cannot interfere with other programs or the operating system.
- The **CPU executes instructions blindly**—it doesn't inherently know whether instructions come from user programs or the OS.
- Therefore, hardware provides **dual modes** of operation:
  - **User Mode**: Executes user-level code with restricted access to hardware resources.
  - **Kernel Mode (Monitor Mode)**: Executes privileged instructions with full access to hardware.

### How Dual Mode Works

- A **mode bit** is maintained in hardware:
  - `1` indicates **User Mode**
  - `0` indicates **Kernel Mode**
- When a user program makes a **system call**, the CPU switches from user mode to kernel mode (by setting the bit to `0`) and begins executing OS code.
- Once the system call is completed, control returns to user mode.
- Privileged instruction is only executed under kernel mode, so user need to use system call 

## I/O Protection

## Memory Protection

## CPU Protection
