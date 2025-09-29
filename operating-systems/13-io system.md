# I/O System

## I/O Hardware
- **Port**: A connection point between I/O devices and the host.  
- **Bus**: A set of **wires** plus a **protocol** that specifies messages sent over the wires.  
- **Controller**: Electronics that operate a port, bus, or device.  

---

## I/O Methods

### Port-Mapped I/O
- Each I/O device is identified by a **unique port address**.  
- Each port consists of **four registers (1–4 bytes each)**:  
  - **Data-in register**: read by host to get input.  
  - **Data-out register**: written by host to send output.  
  - **Status register**: read by host to check device status.  
  - **Control register**: written by host to configure/control the device.  

### Addressing Devices
- **Port-mapped I/O**: uses special I/O instructions with separate address space.  
- **Memory-mapped I/O**: reserves specific memory regions for devices, allowing I/O through normal load/store instructions (more efficient for large devices like GPUs).  

### Interaction Modes
- **Polling (busy-waiting)** – CPU repeatedly checks device status.  
- **Interrupt-driven I/O** – device notifies CPU when ready.  

### Control Methods
- **Programmed I/O** – CPU directly manages all I/O data transfers.  
- **DMA (Direct Memory Access)** – DMA controller transfers data directly between memory and device:  
  - Works with **memory-mapped I/O**.  
  - Uses **interrupts** to notify completion.  
  - Efficient for large data transfers.  

---

## Steps to Handle Interrupt I/O and DMA
1. Device signals interrupt/DMA request.  
2. CPU suspends current execution, saves state, and jumps to interrupt handler.  
3. Interrupt handler or DMA controller coordinates the data transfer.  
4. CPU resumes execution after handling completes.  

---

## Kernel I/O Subsystem
- **I/O scheduling** – reorder requests in the queue to improve throughput/latency.  
- **Buffering** – temporary storage in memory to:  
  - Match speed mismatch between devices.  
  - Adapt to different transfer sizes.  
  - Support copy semantics.  
- **Caching** – keep copies of frequently accessed data in faster memory.  
- **Spooling** – queue output for devices (e.g., printers).  
- **Error handling** – detect and recover from I/O failures.  
- **I/O protection** – enforce privilege levels; only kernel can issue sensitive I/O instructions.  
- **Unix/Linux view** – represent devices as files, exposing memory buffers through a unified interface.  

---

### Blocking & Nonblocking I/O
- **Blocking I/O** – process is suspended until I/O completes.  
- **Nonblocking I/O** – process continues; handled via:  
  - Multithreading  
  - Asynchronous communication  
  - Event-driven programming  

---

### Performance Considerations
- I/O is often a **major system bottleneck**.  
- CPU overhead: executing device driver code, context switching, and cache pollution.  
- Interrupt handling is relatively expensive compared to normal instructions.  

---

### Application Interface
- **Device drivers** – provide a uniform API to I/O subsystem.  
- **Back-door interfaces** – allow device access without new syscalls.  
- **Block devices** – transfer data in fixed-size blocks (e.g., disks).  
- **Character-stream devices** – stream I/O one character at a time (e.g., keyboards, mice, serial ports).