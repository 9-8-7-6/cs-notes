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

## 1. Dual Mode Operation

- The OS must ensure that **incorrect or malicious programs** cannot interfere with other programs or the operating system.
- The **CPU executes instructions blindly**—it doesn't inherently know whether instructions come from user programs or the OS.
- Therefore, hardware provides **dual modes** of operation:
  - **User Mode**: Executes user-level code with restricted access to hardware resources.
  - **Kernel Mode (Monitor Mode)**: Executes privileged instructions with full access to hardware.

- How Dual Mode Works

  - A **mode bit** is maintained in hardware:
    - `1` indicates **User Mode**
    - `0` indicates **Kernel Mode**
  - When a user program makes a **system call**, the CPU switches from user mode to kernel mode (by setting the bit to `0`) and begins executing OS code.
  - Once the system call is completed, control returns to user mode.
  - Privileged instruction is only executed under kernel mode, so user need to use system call 

## 2. I/O Protection

## 3. Memory Protection

- Each program is allocated a specific range of memory it is allowed to access.
- This range is defined by two special registers:
  - **Base Register**: holds the starting address of the program's memory.
  - **Limit Register**: specifies the size (or maximum offset) of the accessible memory region.
- For any memory access to be valid, the following condition must be satisfied:
  - If a program attempts to access memory outside this range, a **trap (exception)** occurs, which the operating system uses to prevent illegal access.
  - These registers can only be modified using **privileged (kernel-mode) instructions**, not by user programs.
  - Note: While `malloc` allocates memory within a program's address space, it **does not change base/limit registers**—those are set by the OS when the program is loaded.

## 4. CPU Protection

- The operating system must prevent user programs from **monopolizing the CPU** or **failing to return control**, which could happen due to:
  - Infinite loops
  - Programs never making system calls or yielding voluntarily

- **Hardware Support: Timer (for time sharing)**
  - A **timer** is initialized by the operating system before transferring control to a user program.
  - The timer is **decremented on every clock tick**.
  - When the timer reaches **zero**, it triggers a **hardware interrupt**.
  - This interrupt forces the CPU to return control to the operating system, allowing it to schedule another process or take appropriate action.

- This mechanism ensures **fair CPU allocation** among processes and prevents any one program from **hogging CPU resources indefinitely**.


# Operating System Services

## 1. User Interface
The OS provides different types of user interfaces:

- **CLI (Command-Line Interface)**  
  A text-based interface that allows users to interact with the system by typing commands.  
  - *Shell*: A command-line interpreter program that executes user commands.

- **GUI (Graphical User Interface)**  

---

## 2. Program Execution
The OS loads programs into memory and executes them. It provides:
- Process creation and termination
- Memory allocation
- Execution environment setup
- Error handling during execution

---

## 3. I/O Operations
The OS manages input and output by providing:
- Interfaces to I/O devices
- I/O buffering and scheduling
- Permissions and control for device access

---

## 4. File-System Manipulation
The OS allows programs and users to:
- Create, delete, read, write, and manage files and directories
- Set and manage access permissions
- Navigate and organize file systems

---

## 5. Communication
Inter-process communication (IPC) methods include:

- **Message Passing**  
  - Process A copies data into kernel space via a system call  
  - Process B retrieves it from kernel space via another system call  
  - Common in distributed systems

- **Shared Memory**  
  - A memory region is shared between processes  
  - Requires system calls to create and manage  
  - Faster but needs synchronization mechanisms

---

## 6. Error Detection
The OS detects and responds to errors:
- In hardware (e.g., memory failures)
- In software (e.g., illegal operations)
- Through logging, alerts, and safe shutdown mechanisms

---

## 7. Resource Allocation
The OS allocates resources to processes such as:
- CPU time
- Memory
- I/O devices
- Files and network connections

---

## 8. Accounting
The OS keeps records of:
- CPU usage
- Memory usage
- Disk activity
- User quotas and billing (in multi-user environments)

---

## 9. Protection and Security
The OS enforces access control to protect:
- Processes from each other
- Users from unauthorized access
- System integrity through authentication, permissions, and encryption
