# File System Interface

---

## Concept
- A **file** is a logical storage unit created by the operating system.  

---

## File Operations

- **Typical file operations**:
  - Create  
  - Write  
  - Read  
  - Reposition (seek within a file)  
  - Delete  
  - Truncate  

- **Tables for managing files**:
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

- **Attributes (metadata):**
  - File pointer (per-process)  
  - File open count (system-wide table)  
  - Disk location (system-wide table)  
  - Access rights (per-process)  

- **File types:**
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
- Often referred to as **random access**, emphasizing the access pattern.  

### 3. Indexed Access
- An **index** contains pointers to blocks of a file.  
- To find a record:  
  1. Search the index file to locate the pointer.  
  2. Use the pointer to directly access the record.  
- For **large files**, the index itself can become very large.  
