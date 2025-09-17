# SQL Database Scaling

## Database performance optimization

### Example Queries

```sql
SELECT * FROM user NATURAL JOIN post WHERE post.date > "2010-01-01" AND user.birth_year < 1920;
```

```sql
SELECT * FROM user NATURAL JOIN post WHERE user.birth_year < 1920 AND post.date > "2010-01-01";
```

### Key Points

- **RAM usage**: Frequently accessed data and indexes are stored in RAM to reduce disk I/O.
- **Caching**: Responses can be cached and replayed if the underlying data has not changed, improving query performance.

---

### Avoid Database Bottleneck:
- Avoid unnecessary queries (e.g., cache data in the frontend).
- Vertical scaling with faster RAM and faster disks (SSD, RAID).

---

## Read Replica
- >95% of DB traffic is **read**.  
- Replica servers maintain a **full copy** of all data.  
- All **write operations** (INSERT, UPDATE, DELETE) must go to the **Primary** server.  
- Data changes are pushed to **read replicas**.  
- **Scaling rule**: The number of replicas `N` should approximately equal `R` times the ratio of reads to writes.  

---

## Multi-Level Replication
- Introduce a **middle replica** layer.  
- Adds an extra level of replication, which increases delay between writes at the primary and data availability at read replicas.  

---

## How to Use Read Replicas
- Place a **load balancer** in front of all read replicas.  
- Load balancer can be:  
  - A **NAT-type local LB**.  
  - A **software library** integrated into the application.  

---

## Shortcomings of Replication
- **Writes are not scalable**: All handled by a single primary DB machine.  
- **Capacity is limited**: Replication mainly improves read performance, not overall database size or write throughput.  

---

### Standby primary
- Keep a **standby** primary ready to take over if the main primary fails
- App will **switch over** to Standby if the main primary stops responding

---

### Why not allow writes to multiple primarys?
- Primary still must handle all writes
- Leads to **inconsistency** if operations happen concurrently

---

### Horizontal scaling of writes and capacity

- Functional Partitioning
  - Divided by tables: Separate multiple databases storing different types of data.
  - Cons:
    - Limits queries joining rows in tables in different databases.
    - Only a few functional partitions

- Data Partitioning(Sharding)
  - **Divided by rows**: Sharding key determines assignment of rows to shards.
  - Relational databases **don't support sharding natively**

- Pros
  - Each rows is stored once
  - Capacity scales
  - Data is consistent
  - If sharding key is chosen carefully:
    - Data will be balanced
    - Many queries will invoke only one or a few shards

- Cons
  - Cannot use plain SQL
  - Queries must be mannually adapted to match sharding
  - If sharding is chosen poorly, shard load will be imbalanced, either by capacity or traffic
  - Some queries may require all shards, limited by the speed of a single machine

---

## Simple Scaling Math

### Basic Concepts
- **N** = number of nodes  
- **R** = total request rate (requests per second or another time frame)  
- **C** = maximum request rate a single node can handle  

---

### Three Scenarios

#### Case 1: Each request goes to **one node**
- Formula: `R_max = N * C`  
- More nodes → higher total capacity.  
- ✅ **Scalable**  

---

#### Case 2: Each request goes to **k fixed nodes**
- Formula: `R_max = (N * C) / k`  
- Still grows with `N`, but divided by `k`.  
- ✅ **Scalable, but less efficient**  

---

#### Case 3: Each request goes to **all nodes**
- Formula: `R_max = C`  
- Every node does the same work, so adding more nodes doesn’t help.  
- ❌ **Not Scalable**  

---

### Summary Table

| Request Distribution | Max Capacity Formula | Scalability |
|-----------------------|----------------------|-------------|
| One node             | `N * C`              | ✅ High     |
| k nodes              | `(N * C) / k`        | ✅ Medium   |
| All nodes            | `C`                  | ❌ None     |

---

### Key Takeaway
- For scalability, **requests must be distributed**.  
- If every node repeats the same work (Case 3), adding nodes provides no benefit.  
