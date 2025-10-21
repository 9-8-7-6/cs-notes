# Mass Storage System

## Disk Structure
- **Logical view**: disk is a **1-dimensional array of logical blocks**.  
- **Sectors per Track**:  
  - **Constant Linear Velocity (CLV)** – uniform density; used in optical disks (CD/DVD).  
  - **Constant Angular Velocity (CAV)** – fixed rotation speed; outer tracks hold more data; common in HDDs.  

---

## Disk I/O
- Disks connect to the computer via an **I/O bus**.  
- Common interfaces: **EIDE, ATA, SATA, USB, SCSI**.  
- **I/O bus controllers**:  
  - **Host controller** – on the computer side.  
  - **Disk controller** – built into the disk drive.  

---

## Disk Scheduling

### Performance Factors
- **Seek time** – move the disk arm to the target cylinder.  
- **Rotational latency** – wait for the desired sector to rotate under the head.  
- **Transfer time** – time to read/write data once positioned.  

### Scheduling Algorithms
- **FCFS (First-Come First-Served)**  
  - Simple, fair, but can cause long waits.  

- **SSTF (Shortest Seek Time First)**  
  - Chooses request closest to current head position.  
  - Reduces seek time but may cause starvation.  

- **SCAN (Elevator Algorithm)**  
  - Head moves in one direction servicing requests, then reverses.  
  - More fair than SSTF.  

- **C-SCAN (Circular SCAN)**  
  - Head moves in one direction servicing requests, then jumps back to the beginning.  
  - Provides uniform wait times.  

- **C-LOOK**  
  - Variant of C-SCAN: head only goes as far as the last request in that direction, then returns.  

---

## Disk Management

### Disk Formatting
1. **Low-level (physical) formatting**: divide a disk into sectors (header + data area + trailer).  
2. **Partitioning**: divide disk into one or more groups of cylinders.  
3. **Logical formatting**: creation of a file system.  

---

### Bootstrap Block
- **First bootstrap code** stored in ROM.  
- **Complete bootstrap** stored in the boot block of the system disk.  

---

### Bad Blocks
- **Simple disks (IDE)**  
  - Mark bad block in the FAT entry.  

- **Sophisticated disks (SCSI)**  
  - Controller maintains list of bad blocks.  
  - **Sector sparing (forwarding)** – remap block to a spare one.  
  - **Sector slipping** – shift sectors down one spot.  

---

## Swap-Space Management

- **Swap-space**: disk space used as an extension of main memory.  
- **Location options**:  
  1. Part of a normal file system.  
  2. Separate raw disk partition.  
  3. Systems may allow both types.  

### Swap-Space Allocation

1. **Process-level swapping**  
   - Copy the **entire process** image into disk when loading into memory or swapping out.  
   - Used in early systems; inefficient for large processes.  

2. **Page-level swapping**  
   - Copy only a **single page** to swap space when a page fault or page-out occurs.  
   - More efficient and flexible than full-process swapping.  
   - **Strategies**:  
     1. Swap **runtime anonymous memory** (stack, heap) only, excluding text segment (binary code).  
     2. Swap **runtime anonymous memory** (stack, heap) on **page-out**, still excluding text segment (binary code).  
        - The text segment is usually kept read-only and can be reloaded from the program binary on disk instead of being swapped.  

### Swap-Space Structure
- Uses an array or table to track which swap slots are **empty** and which are **occupied**.  

---

## RAID  
**Redundant Arrays of Inexpensive Disks (RAID)**: A storage system that combines multiple disks to improve reliability and/or performance.  

- **Reliability** via redundancy  
- **Performance** via parallelism  
- Techniques: **Striping**, **Mirroring**, **Error-Correcting Code (ECC)**, **Parity bit**  

---

### RAID 0 – Non-redundant Striping
- **Goal**: Improve performance.  
- **Method**: Data is **striped** across N disks.  
- **Pros**:  
  - High I/O bandwidth (parallel access).  
- **Cons**:  
  - No redundancy → single disk failure causes total data loss.  

---

### RAID 1 – Mirrored Disks
- **Goal**: Provide reliability via redundancy.  
- **Method**: Data is **duplicated** (mirrored) across 2 disks.  
- **Performance**:  
  - **Read** bandwidth: increases up to N times (parallel reads).  
  - **Write** bandwidth: remains the same (data must be written to both disks).  
- **Storage efficiency**: 1:1 (50% usable).  

---

### RAID 2 – Hamming Code
- **Goal**: Error correction.  
- **Method**: Uses **Hamming code ECC** to detect and correct errors.  
- **Characteristics**:  
  - Can recover from **any single-disk failure**.  
  - Example: (7,4) code → 4 data bits stored on 4 disks + 3 parity bits stored on 3 disks.  
- **Storage ratio**: 4:3.  
- Rarely used in practice due to high overhead.  

---

### RAID 3 & RAID 4 – Parity Bit
- **Goal**: Single-disk failure recovery using parity.  
- **Method**: Disk controller uses parity to check/correct errors.  
- **RAID 3**:  
  - **Bit-level striping** (1 bit at a time across disks).  
  - Requires synchronized disk rotation.  
  - Parity stored on a dedicated disk.  
- **RAID 4**:  
  - **Block-level striping** (entire blocks distributed across disks).  
  - Dedicated parity disk used for recovery.  
  - Better for independent I/O requests than RAID 3.  

---

### RAID 5 – Distributed Parity
- **Goal**: Balance performance and reliability.  
- **Method**: Data and parity bits are **distributed across all disks**.  
- **Pros**:  
  - Avoids bottleneck of a single dedicated parity disk.  
  - Good **read** performance, improved **write** compared to RAID 4.  
- **Cons**:  
  - Still vulnerable to two-disk failures.  
- **Storage efficiency**: (N – 1)/N.  

---

### RAID 6 – P + Q Dual Parity
- **Goal**: Tolerate multiple disk failures.  
- **Method**: Stores **two independent parity blocks** (P and Q) using **Reed-Solomon ECC** or equivalent codes.  
- **Pros**:  
  - Can survive **up to 2 simultaneous disk failures**.  
- **Cons**:  
  - More complex parity calculations.  
  - Write performance is slower than RAID 5.  
- **Storage efficiency**: (N – 2)/N.  
