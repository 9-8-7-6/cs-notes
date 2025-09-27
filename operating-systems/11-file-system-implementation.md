# File System Implementation

---

## File-System Structure

- I/O transfers between memory and disk are performed in units of **blocks**.  
  - One block is one or more **sectors**.  
  - One sector is usually **512 bytes**.  

- One OS can support more than one **file system type**.  
  - Examples: **NTFS**, **FAT32**.  
  - Each FS may differ in:  
    - Disk allocation method.  
    - Search/indexing implementation.  

- Two main design problems in file system:  
  1. **Interface to user programs**  
     - How programs see and interact with files (APIs, syscalls, abstractions).  
  2. **Interface to physical storage (disk)**  
     - How the OS translates logical operations into physical disk I/O.  

---

## Layered File System

A **layered file system** separates responsibilities into multiple layers,  
so that **file system APIs** are gradually mapped down to **physical disk locations**.

### Concept

- **High-level API** (e.g., `open`, `read`, `write`) → user program interaction.  
- **Logical file system** → maintains directories, file names, metadata, access control.  
- **Mapping**:  
  - Logical file system → **logical blocks**.  
  - File-organization module → maps logical blocks → **physical blocks**.  
- **Physical storage** → actual sectors/blocks on disk.  

### Layer Structure

1. **User Interface Layer**  
   - Provides system calls (`open`, `close`, `read`, `write`).  
   - User programs interact only with this layer.  

2. **Logical File System**  
   - Manages metadata (file control blocks, inodes).  
   - Performs logical-to-logical mapping (file name → file descriptor → logical blocks).  
   - Protection and access rights are checked here.  

3. **File-Organization Module**  
   - Implements file allocation methods.  
   - Maps logical blocks → **physical blocks on disk**.  
   - Maintains free-space management.  

4. **Basic File System**  
   - Passes physical block I/O requests to the I/O layer.  
   - Responsible for buffering, caching, and scheduling requests.  

5. **I/O Control**  
   - Device drivers + interrupt handlers.  
   - Translates OS commands to hardware operations.  

6. **Devices (Disks)**  
   - Lowest layer: physical blocks, sectors, tracks, cylinders.  
   - Provides raw data storage.  

---

## On-Disk Structure *(Permanent, stored in File Control Block – FCB)*

- **Boot Control Block** *(per partition)*  
  - Contains information needed to boot an OS from that partition.  

- **Partition Control Block** *(per partition)*  
  - Stores details of the partition:  
    - Number of blocks.  
    - Block size.  
    - Free-block list.  
    - Free File Control Block (FCB) pointers.  
  - Examples:  
    - UFS → **Superblock**.  
    - NTFS → **Master File Table (MFT)**.  

- **File Control Block (FCB)** *(per file)*  
  - Created after formatting.  
  - Contains details regarding a file:  
    - Permissions.  
    - File size.  
    - Location of data blocks.  
  - Examples:  
    - UFS → **inode**.  
    - NTFS → stored inside **MFT** (as relational records).  

- **Directory Structure** *(per file system)*  
  - Created after formatting.  
  - Provides organization and hierarchical structure for files.  

---

## In-Memory Structure *(Volatile, stored in RAM)*

- **In-memory partition table**  
  - Information about each **mounted partition**.  

- **In-memory directory structure**  
  - Information of **recently accessed directories**.  

- **System-wide open-file table**  
  - Contains a copy of each **opened file's FCB**.  

- **Per-process open-file table**  
  - Holds pointers (file handlers/descriptors) to corresponding entries in the **system-wide open-file table**.  

---

## Procedure Examples

1. **Read**  
   - Application issues a `read()` call.  
   - OS translates file descriptor → system-wide open-file entry → FCB → disk blocks.  
   - Requested blocks are read into memory and returned.  

2. **Write**  
   - Application issues a `write()` call.  
   - Data is placed into buffer cache.  
   - OS updates in-memory FCB and later flushes data to disk blocks.  

3. **File Creation**  
   1. OS allocates a new **FCB**.  
   2. Update **directory structure**:  
      - OS reads the corresponding directory into memory.  
      - Adds the new file name and FCB reference.  
      - When the file is closed, OS writes the updated directory structure back to disk.  
   3. The file becomes visible in the user's directory listing.  

---

## Virtual File System (VFS)

Linux VFS defines four main object types:

- **inode** → represents an individual **file**.  
- **file object** → represents an **open file**.  
- **superblock object** → represents an entire **file system**.  
- **dentry object** → represents an individual **directory entry**.  

---

## Directory Implementation

- **Linear List**  
  - List of file names with pointers to data blocks.  
  - Easy to implement but poor performance:  
    - Insertion, Deletion, Searching are slow.  

- **Hash Table (linear list + hash data structure)**  
  - Provides near constant-time searching.  
  - Uses linked lists for collisions on a hash entry.  
  - Hash table usually has a fixed number of entries.  

---

## Allocation Method

- An allocation method refers to how disk blocks are allocated for files.  

### Allocation Strategy

1. **Contiguous allocation**  
   - Each file occupies a set of contiguous blocks.  
   - Sequential & random access implemented efficiently.  
   - **Problems**:  
     - External fragmentation → compaction.  
     - File cannot grow → extent-based FS.  
   - **Extent**: One or more contiguous blocks.  
   - **Extent structure**: Links several extents.  
   - Random access becomes more costly in extent-based FS.  
   - Both internal & external fragmentation possible.  

2. **Linked allocation**  
   - Each file is a linked list of blocks.  
   - Each block contains a pointer to the next block.  
   - Data portion = block size − pointer size.  
   - Good only for **sequential access**.  
   - Space overhead: pointer (e.g., 4/512 = 0.78%).  
     - **Solution**: group into clusters of blocks → internal fragmentation.  
   - Reliability issue: one missing link breaks the whole file.  
   - **FAT (File Allocation Table) file system**  
     - **FAT32**:  
       - Used in MS-DOS & OS/2.  
       - Stores all links in a table.  
       - 32 bits per table entry.  
       - Located in a section of disk at the **beginning of each partition**.  
     - FAT table is often *cached in memory*.  

3. **Indexed allocation**  
  - The directory contains the address of the file index blocks.  
  - Each file has its own index block.  
  - Index block stores block numbers for file data.  
  - Schemes:
    1. Linked indexed scheme: use linked list to connect index block
    2. Multilevel scheme(two-level)
    3. Combined Scheme: UNIX inode

---

## Free-Space Management

- **Free-space list** – records all free blocks  
- Schemes:  
  - **Bit vector** (bitmap) – simple, efficient, but costly for large partitions  
  - **Linked list** – free blocks linked together  
  - **Grouping** – store addresses of free blocks in blocks themselves  
  - **Counting** – record start + length of free block runs  
