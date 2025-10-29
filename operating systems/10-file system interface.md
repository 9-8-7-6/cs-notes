# File System Interface

---

## Concept
- A **file** is a logical storage unit created by the operating system.  

---

## File Operations

### Typical File Operations
- Create  
- Write  
- Read  
- Reposition (seek within a file)  
- Delete  
- Truncate  

### Tables for Managing Files
- **Per-process open-file table**  
  - Metadata specific to each process that has opened files.  
- **System-wide open-file table**  
  - Metadata shared across all processes in the system.  

---

## Open-File Tables

### 1. Per-Process Table
- Tracks all files opened by this process.  
- Maintains the **current file pointer** for each opened file.  
- Stores **access rights** and **accounting information**.  

### 2. System-Wide Table
- Each entry in the per-process table points to this table.  
- Contains process-independent information, such as:  
  - Disk location of the file  
  - Access dates  
  - File size  
- Includes an **open count** (number of processes that have the file opened).  

---

## Open-File Attributes

### Attributes (Metadata)
- File pointer (per-process)  
- File open count (system-wide table)  
- Disk location (system-wide table)  
- Access rights (per-process)  

### File Types
- Examples: `.exe`, `.com`, `.obj`, `.cc`, `.mov`, etc.  
- Serves as a *hint* for the OS to operate on the file in a *reasonable* way.  

---

## Access Methods

### 1. Sequential Access
- Read/write the **next block**.  
- **Reset**: reposition the file pointer to the beginning.  
- **Skip/Rewind**: move forward or backward by *n* records.  

### 2. Direct (Relative) Access
- Access an element at an **arbitrary position** in a file.  
- File operations include the **block number** as a parameter.  
- Also called **random access**, highlighting the access pattern.  

### 3. Indexed Access
- An **index** contains pointers to blocks of a file.  
- To find a record:  
  1. Search the index file to locate the pointer.  
  2. Use the pointer to directly access the record.  
- For **large files**, the index itself can become very large.  

---

## Partition, Volume, Directory

### Partition
- A partition is a logically defined contiguous region of a physical storage device.
- It divides a disk into separate sections, each with its own starting and ending block.
- A partition itself does not imply any specific data structure.

### Volume
- A volume is a logical storage unit created from a formatted partition with a filesystem.
- Once a filesystem is applied, the partition becomes a volume that the operating system can mount and use to store files.

### Directory
- Stores information about the files located in the partition/volume.  
- Provides a **hierarchical structure** (tree) for organizing files.  
- A *collection of nodes* containing information about all files.  

#### Directory Organization
1. **Single-Level Directory**  
    - All files in one directory.  
    - Filenames must be unique.  
    - Poor efficiency for locating a file when many files exist.  

2. **Two-Level Directory**  
   - A separate directory for *each user*.  
   - Path = username + filename.  

3. **Tree-Structured Directory**  
   - **Absolute path**: starts from the *root*.  
   - **Relative path**: starts from a *directory*.  

4. **Acyclic-Graph Directory**  
   - Uses links to share files or directories.  
   - UNIX: **symbolic links**.  
   - A file may have multiple absolute paths.  
   - Deletion cases:  
     - Delete the link but not the file.  
     - Delete the file but not the link → dangling pointer.  

5. **General-Graph Directory**  
    - May contain cycles
    - Reference count doesn't work
    - Garbage collection: Traverse the entire graph from the root and delete the unreachable node

---

## File System Mounting
- A file system must be **mounted** before it can be accessed.  
- **Mount point**: root path where a filesystem is mounted.  
- **Mount time**:  
  - At boot time.  
  - Automatically at run-time.  
  - Manually at run-time.  

---

## File Sharing for Multiple Users
- **User identity**: each user has a `userID` and `groupID`.  
- **File ownership**: each file has an **owner**, **group**, and **others**.  

---

## File Protection
- Files should be kept from
  - physical damage
  - improper access