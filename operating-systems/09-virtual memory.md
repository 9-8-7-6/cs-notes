# Virtual Memory
> Separation of logical memory from physical memory for `better memory utilization`

---

## Advantage
- Run **extremely large process**
- Increase **CPU/resource utilization**(more processes can be used)
- Program ran **faster** : Less program need loaded , just the page we need

---

## Implementation of Virtual Memory

### Concept of Demand
> Bringing into memory **only what is needed**

---

### Demand Paging

#### **How it works**:
- Start executing a process **without page in memory**
- A page is loaded **only if referenced**

#### **Benefits**:
- Less I/O -> faster response
- Less memory required -> More users are supported simultaneously

#### **Hardware support**
- **Page Table** with a *valid-invalid bit*
    - `1` -> page in memory
    - `0` -> page not in memory
    - initially, all bits are `0`

#### **Comparison**:
- **Swapper (midterm scheduler)** -> swaps the **entire process**
- **Pager** -> swaps **individual pages** of a process

---

#### **Page Fault**
> Occurs when a page is referenced but not in memory lead to trap to OS

1. OS checks PCB:
    - invalid reference -> abort
    - if valid but not in memory -> continue
2. Find a **empty frame**, if none, swap out memory with `replacement algorithms`
3. Swap in the page from disk
4. Update the page table -> set valid-invalid bit = 1
5. **Restart instruction** (program count will plus 4 bytes after the instruction, so need to switch 4 bytes back )

---

#### Demand Paging Performance

- Effective Access Time(EAT): (1 - p) * ma + p * pft
    - p: page fault rate
    - ma: memory access time
    - pft: page fault time

---

#### Process Creation & Virtual Memory

- **Demand Paging**: Only load the page containing the first instruction
- **Copy-on-Write**: parent and child share frames initially and frame-copy when a page is written
- **Memory-Mapped File**: map a file into the virtual address space bypassing traditional file system calls

---

### Page Replacement
> Select which frame to be replaced when a page fault occurs wihout free frame

- Swap out a process.
- **Page replacement**: find a process not currently used and free it.
    - Use **dirty bit** on page to identify the pages is modified -> reduce disk's I/O.

#### Page Replacement Algorithms

- **FIFO**: the oldest page in a FIFO queue is replaced

- **Optimal**: the longest period of time **will not** being used is replaced

- **LRU**(Least Recently Used): the longest period of time not being used is replaced
    - Counter implementation: use *timestamp* for each access
    - Stack: use a stack/doubly-linked list, remove the page at the bottom.

- **Counting**  
  Use counters to track how often a page is accessed.  

  - **LFU (Least Frequently Used)**: replace the page with the **lowest reference count**.  
    - Idea: pages less used in the past are unlikely to be used soon.  
    - Problem: a once-hot page may stay forever even if no longer needed.  

  - **MFU (Most Frequently Used)**: replace the page with the **highest reference count**.  
    - Idea: a heavily used page was likely brought in long ago and may not be needed further.  
    - Opposite of LFU; rarely used in practice.

---

### Demand Segmentation
- Demand Segmentation: better for programmer’s perspetive

