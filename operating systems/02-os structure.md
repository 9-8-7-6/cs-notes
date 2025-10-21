# OS-Structure

## Operating System Services

### 1. User Interface
The OS provides different types of user interfaces:

- **CLI (Command-Line Interface)**  
  A text-based interface that allows users to interact with the system by typing commands.  
  *Shell*: A command-line interpreter program that executes user commands.

- **GUI (Graphical User Interface)**  

---

### 2. Program Execution
The OS loads programs into memory and executes them. It provides:
- Process creation and termination
- Memory allocation
- Execution environment setup
- Error handling during execution

---

### 3. I/O Operations
The OS manages input and output by providing:
* Interfaces to I/O devices
* I/O buffering and scheduling
* Permissions and control for device access

---

### 4. File-System Manipulation
The OS allows programs and users to:
- Create, delete, read, write, and manage files and directories
- Set and manage access permissions
- Navigate and organize file systems

---

### 5. Communication
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

### 6. Error Detection
The OS detects and responds to errors:
- Hardware (e.g., memory failures)
- Software (e.g., illegal operations)

---

### 7. Resource Allocation
The OS allocates resources to processes such as:
- CPU time
- Memory
- I/O devices
- Files and network connections

---

### 8. Accounting
The OS keeps records of:
- CPU usage
- Memory usage
- Disk activity
- Resource usage and billing (in multi-user environments)

---

### 9. Protection and Security
The OS enforces access control to protect:
- Processes from each other
- Users from unauthorized access
- System integrity through authentication, permissions, and encryption


## Difference between Api and System Call

### System Call

- Services
    - Process Control : abort,create, terminate process, allocate/free memory
    - File management : create, delete, open, close file
    - Device management : read, write, reposition device
    - Communication - send receive message


- How System Call was called
    - User program calls the OS API
    - The API translates the request into a system call
    - CPU executes a software interrupt to switch from **user mode** to **kernel mode**

### API
- Users mostly program with APIs instead of system call
- Common language libraby
- Not all API calls involve system calls; some are implemented entirely in user space
- An API call may use multiple system calls
- Common APIs:
    - **Win32 Api** for Windows
    - **POSIX API** for POSIX-based system(UNIX, Linux, Mac OS X)
    - **Java API** for java virtual machine 


### The order of Api and System Call
```markdown
        User Mode:
+------------------------+
|   User Application     |
|    calls open()        |
+------------------------+
            |
            v
+------------------------+
|  System Call Interface |
+------------------------+

      Kernel Mode:
            |
            v
+--------------------------+
|  System Call Table (i)   |
+--------------------------+
            |
            v
+-----------------------------------------+
| open() Implementation in Kernel Space   |
+-----------------------------------------+
            |
            v
+--------------------------+
|    Return to User App    |
+--------------------------+
```

### Layered OS
> A Layered Operating System is structured as a hierarchy of layers, each built on top of the lower one.

#### Key Features:
- Each layer only interacts with the layer directly below it.
- Simplifies debugging and maintenance due to modular design.
- Lower layers provide core functionalities; higher layers provide more abstract services.

### Microkernel OS
- Leave most important in kernel, move others from kernel into **user space**

- Communication by message passing

### Modular OS
- All in kernel modules
- Uses object-oriented approach

## Virtual Machine

### Concept
- A layered approach to treat hardware and operating system kernel as they were all hardware
- The guest OS inside the VM thinks it runs in kernel mode, but actually runs in user mode.

---

### How Privileged Instructions Are Handled
1. The guest OS inside the VM executes privileged instructions(in user mode)
2. The virtual machine monitor (VMM) or hypervisor intercepts it
3. The interrupt/exception(trap) is detected by the host OS or hypervisor.
4. The hypervisor fakes(emulates) the behavior of the hardware for the VM.
5. The instruction is then re-executed or handled safely,maintaining isolation and security.

---

### Critical Instruction
- Critical instructions are those that behave differently in user mode and kernel mode

---

### Feature
- Provides complete protection of system resources
- Provides a way to solve system compatibility problems
- Provides an environment for research and development
- Increase resources utilization in cloud computing

--- 
### Category
- Full Virtualization (e.g., VMware, VirtualBox)
  - Emulates the entire hardware stack, allowing unmodified guest OSes to run.
  - Requires hardware support (e.g., Intel VT-x, AMD-V) or binary translation.
- Paravirtualization (e.g., Xen)
  - The guest OS is modified to be aware of virtualization, reducing overhead.
  - Relies on hypercalls instead of trapping all privileged instructions.
- Process-level Virtualization (e.g., Java Virtual Machine)
  - Provides a virtual runtime environment for executing programs in a specific language.
  - Does not virtualize hardware, but abstracts the operating system and CPU for portability.