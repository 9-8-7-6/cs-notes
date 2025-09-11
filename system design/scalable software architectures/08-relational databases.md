# Relational Databases

## Why a Relational Database?

### Most importantly:
- **Scalability** – work with data larger than computer’s RAM.  
- **Persistence** – keep data around after your program finishes.  
- **Indexing** – efficiently sort & search along various dimensions.  
- **Concurrency** – multiple users or applications can read/write.  
- **Analysis** – SQL query language is concise yet powerful.  

### And also:
- **Integrity** – restrict data type, disallow duplicate entries, transactions.  
- **Deduplication** – save space, keep common data consistent.  
- **Security** – different users can have access to specific data.  

### Indexing

> DB index use tree or hashtable instead of sorting

---

## Redundant Array of Independent Disks (RAID)

> Combine many disks to create a superior virtual disk

### Disk shortcomings:
1. Limited **capacity**  
2. Limited **throughput**  
3. Likelihood of **failure**  

### RAID advantages:
1. Increase **capacity** by combining multiple disks.  
2. Increase **throughput** by accessing data in parallel.  
3. Reduce disk **failure risk** by storing data redundantly.  

### Concept:
- Create a **logical/virtual disk** made of sectors from multiple physical disks.  
