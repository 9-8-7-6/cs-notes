# Multithreaded Programming

> A thread has its own **Thread Control Block (TCB)**, **thread ID**, **program counter**, **register set**, and **stack** (not shared among threads).

---

## Benefits of Multithreading
1. **Responsiveness** – improve interactive performance.  
2. **Resource sharing** – threads share the same memory space.  
3. **Utilization of Multiprocessor Architecture** – true **parallelism**.  
4. **Economy** – lighter than processes, better resource utilization.  

---

## Multithreaded Programming Categories
- **Shared-memory model** (multithreading)  
- **Message-passing model**

---

## Challenges
1. **Dividing tasks** – split program into concurrent tasks.  
2. **Data splitting** – partition data to be accessed/manipulated by tasks.  
3. **Data dependency** – synchronize data access to avoid race conditions.  
4. **Balance** – evenly distribute tasks to cores.  
5. **Testing and debugging** – harder than sequential programs.  

---

## User Threads vs. Kernel Threads

- **User Threads**  
  - Managed in **user space** by a threads library.  
  - Examples: POSIX Pthreads, Win32 threads, Java threads.  

- **Kernel Threads**  
  - Directly supported and managed by the **OS kernel**.  

---

## Multithreading Models

### 1. Many-to-One
- Many user threads map to **one kernel thread**.  
- Limitation: if one thread makes a blocking call, the entire process blocks.  
- Only one thread can access the kernel at a time → **no parallelism** on multiprocessors.  

![Many-to-One](https://media.geeksforgeeks.org/wp-content/cdn-uploads/gq/2015/07/many_to_many2-300x200.jpg)

---

### 2. One-to-One
- Each user thread maps to a **kernel thread**.  
- Provides concurrency and parallelism.  
- Limitation: number of kernel threads is restricted.  

![One-to-One](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcS39QxRE-Hk4F6AIPxdqRKEOEDhe4Du38tQlg&s)

---

### 3. Many-to-Many
- Many user threads map to a smaller or equal number of kernel threads.  
- Allows creation of as many user threads as needed.  
- Provides flexibility and better resource usage.  

![Many-to-Many](https://media.geeksforgeeks.org/wp-content/cdn-uploads/gq/2015/07/many_to_many1-300x200.jpg)
