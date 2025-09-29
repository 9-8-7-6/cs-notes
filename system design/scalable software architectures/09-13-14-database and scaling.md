# SQL Database Scaling

## Part 1. SQL Database Scaling

### Database performance optimization

#### Example Queries

```sql
SELECT * FROM user NATURAL JOIN post WHERE post.date > "2010-01-01" AND user.birth_year < 1920;
```

```sql
SELECT * FROM user NATURAL JOIN post WHERE user.birth_year < 1920 AND post.date > "2010-01-01";
```

#### Key Points

- **RAM usage**: Frequently accessed data and indexes are stored in RAM to reduce disk I/O.
- **Caching**: Responses can be cached and replayed if the underlying data has not changed, improving query performance.

---

#### Avoid Database Bottleneck:
- Avoid unnecessary queries (e.g., cache data in the frontend).
- Vertical scaling with faster RAM and faster disks (SSD, RAID).

---

### Read Replica
- >95% of DB traffic is **read**.  
- Replica servers maintain a **full copy** of all data.  
- All **write operations** (INSERT, UPDATE, DELETE) must go to the **Primary** server.  
- Data changes are pushed to **read replicas**.  
- **Scaling rule**: The number of replicas `N` should approximately equal `R` times the ratio of reads to writes.  

---

### Multi-Level Replication
- Introduce a **middle replica** layer.  
- Adds an extra level of replication, which increases delay between writes at the primary and data availability at read replicas.  

---

### How to Use Read Replicas
- Place a **load balancer** in front of all read replicas.  
- Load balancer can be:  
  - A **NAT-type local LB**.  
  - A **software library** integrated into the application.  

---

### Shortcomings of Replication
- **Writes are not scalable**: All handled by a single primary DB machine.  
- **Capacity is limited**: Replication mainly improves read performance, not overall database size or write throughput.  

---

#### Standby primary
- Keep a **standby** primary ready to take over if the main primary fails
- App will **switch over** to Standby if the main primary stops responding

---

#### Why not allow writes to multiple primaries?
- Primary still must handle all writes
- Leads to **inconsistency** if operations happen concurrently

---

#### Horizontal scaling of writes and capacity

- Functional Partitioning
  - Divided by tables: Separate multiple databases storing different types of data.
  - Cons:
    - Limits queries joining rows in tables in different databases.
    - Only a few functional partitions

- Data Partitioning(Sharding)
  - **Divided by rows**: Sharding key determines assignment of rows to shards.
  - Relational databases **don't support sharding natively**

- Pros
  - Each row is stored once
  - Capacity scales
  - Data is consistent
  - If sharding key is chosen carefully:
    - Data will be balanced
    - Many queries will invoke only one or a few shards

- Cons
  - Cannot use plain SQL
  - Queries must be manually adapted to match sharding
  - If sharding is chosen poorly, shard load will be imbalanced, either by capacity or traffic
  - Some queries may require all shards, limited by the speed of a single machine

---

### Simple Scaling Math

#### Basic Concepts
- **N** = number of nodes  
- **R** = total request rate (requests per second or another time frame)  
- **C** = maximum request rate a single node can handle  

---

#### Three Scenarios

##### Case 1: Each request goes to **one node**
- Formula: `R_max = N * C`  
- More nodes → higher total capacity.  
- ✅ **Scalable**  

---

##### Case 2: Each request goes to **k fixed nodes**
- Formula: `R_max = (N * C) / k`  
- Still grows with `N`, but divided by `k`.  
- ✅ **Scalable, but less efficient**  

---

##### Case 3: Each request goes to **all nodes**
- Formula: `R_max = C`  
- Every node does the same work, so adding more nodes doesn’t help.  
- ❌ **Not Scalable**  

---

#### Summary Table

| Request Distribution | Max Capacity Formula | Scalability |
|-----------------------|----------------------|-------------|
| One node             | `N * C`              | ✅ High     |
| k nodes              | `(N * C) / k`        | ✅ Medium   |
| All nodes            | `C`                  | ❌ None     |

---

#### Key Takeaway
- For scalability, **requests must be distributed**.  
- If every node repeats the same work (Case 3), adding nodes provides no benefit.  

---

## Part 2. Distributed NoSQL Databases

---

### Normalized Data
- In relational databases, **normalization** avoids duplication of data.  
- Shared data is referenced via **foreign keys** or **IDs**.  

---

### NoSQL
- Removes the ability to create references between records.  
- Stores **denormalized data** in a **key → value store**, with copies of referenced data included.  

---

### Hashing
- A **hash** is an algorithm that takes an input and returns a pseudo-random fixed-length value.  
- Properties:  
  - Same input → same output.  
  - Output length is constant.  

- **Hash Table**:  
  - Stores `(key, value)` pairs (like a dictionary or map).  
  - The key is hashed to determine the storage address.  
  - If the slot is already filled (collision), the system uses the next open slot.  

---

### Distributed Hash Table (DHT)
- Each **cluster node** is responsible for a **range of hash values**.  
- Client computes the **hash of the key** to decide which node to query.  

---

### Downsides
- Only one indexed column (the **key**).  
- Denormalized data issues:  
  - **Wastes space** (duplicate data).  
  - Cannot be edited in one place (updates require multiple copies).  
- References may exist, but there is **no constraint checking** (e.g., no foreign keys).  

---

## Part 3. Distributed DB Consistency

---

### Consistency
- When data is **replicated** across multiple nodes, there is always a possibility of **inconsistency**.  

- **CAP Theorem**  
  1. **Consistency** – Every request always gets the most recent write.  
  2. **Availability** – Every request receives a non-error response.  
  3. **Partition tolerance** – The system continues to function despite network partitions (dropped or delayed messages).  

- When distributed DB nodes are **out-of-sync** (partitioned), systems must choose:  
  - Accept **inconsistent responses**, or  
  - Wait until nodes **resynchronize** (adds latency).  

- A **perfectly consistent distributed system** would require a **100% reliable, zero-delay network** → not realistic.  
- The CAP theorem implies a **tradeoff between consistency and delay/availability**.  
- Inconsistency often leads to **hard-to-debug errors**.  
- Distributed (NoSQL) databases provide options to configure this **consistency vs. latency tradeoff**.  

---

### Client-Centric Consistency Properties

- **Monotonic Reads**  
  - Once a client reads `x`, later reads of `x` must return the same or a more recent value.  
  - **Issue**: Reading from two different nodes during an incomplete write may return inconsistent values.  
  - **Fix**:  
    - Make the client connect to the **same node** for every request, or  
    - Delay the second read until replicas catch up.  

- **Read Your Writes**  
  - Once a client writes `x`, later reads of `x` must return that value or a newer one.  
  - **Issue**: The first write has not yet propagated to all replicas.  
  - **Fix**:  
    - Stick with one node (write + read), or  
    - Delay subsequent reads until replicas are updated.  

- **Monotonic Writes**  
  - If a client issues two writes to `x`, the system must ensure the first write is applied before the second.  
  - **Issue**: The first write has not yet reached a replica when the second write is sent to a different node.  
  - **Fix**:  
    - Enforce **write ordering** by routing all writes for the same client/key to the same node, or  
    - Use a coordination mechanism (e.g., version vectors, Lamport clocks) to order writes.  

---

### Alternatives for Achieving Consistency
1. **Client directs all requests to one replica node**  
   - Simple to implement.  
  - Risky if that node fails (single point of failure).  

2. **Client waits for synchronization across the system**  
  - Guarantees global consistency.  
  - Increases latency; simplest approach is to send the request to **all nodes** and wait for confirmation.  

### What if a DHT Replica Fails?

In a **Distributed Hash Table (DHT)**, data is assigned to nodes based on the hash of the key.  
When a replica (or node) fails, several issues and strategies arise:

---

#### Issues
- **Lost availability**: Keys assigned to that node become temporarily inaccessible.  
- **Inconsistency**: If the failed replica had not synchronized with others, the latest writes may be lost.  
- **Load imbalance**: Remaining nodes must take over responsibility for the missing hash range.  

---

#### Common Strategies

1. **Replication Factor (r replicas per key)**  
   - Each key is stored on multiple nodes (not just one).  
   - Example: store `key → value` on the node responsible + next `r-1` successors on the hash ring.  
   - If one replica fails, other replicas still serve requests.  

2. **Successor/Predecessor Lists (Consistent Hashing)**  
   - Each node maintains knowledge of its neighbors in the hash ring.  
   - If a node fails, its successor or predecessor takes over responsibility for its key range.  

3. **Re-replication / Repair**  
   - When failure is detected, the system automatically **re-replicates** missing keys to new healthy nodes.  
   - Background processes (e.g., *anti-entropy*, *Merkle tree sync*) periodically check and restore consistency.  

4. **Quorum Protocols (N, R, W model)**  
   - `N`: total replicas per key  
   - `R`: minimum replicas that must respond for a read  
   - `W`: minimum replicas that must acknowledge a write  
   - As long as `R + W > N`, strong consistency can be ensured even with failures.  

---

### Another Way of Looking at Consistency

- A distributed system is **linearizable** if the partial ordering of actions is preserved globally.  
- Each actor (client/node) knows the order of its **own operations**.  
- Together, these define a **partial order** of all events.  
- Any global serialization (a single logical timeline of events) must be **consistent with each actor’s local order**.  
- Different observers may see different valid serializations, but each must respect the individual constraints.  
