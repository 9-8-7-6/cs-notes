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

---

## Part 4. Choosing a Database

---

### SQL Relational Database
- Data is organized into **tables**, with **foreign keys** to establish relationships.  
- Supports **transactions**:  
  - A sequence of operations is committed **all-or-none** (ACID properties).  
- **Write scalability**:  
  - Writes typically must go through **one master node**.  
  - Horizontal write scaling is difficult (requires sharding).  
- **Read scalability**:  
  - Read-replicas can help scale read performance, but with some replication **delay/lag**.  
- Best suited for:  
  - Strong consistency requirements.  
  - Applications that need **complex queries** (JOINs, aggregations).  
  - Structured, relational data with well-defined schemas.  

---

### Transactions on Distributed (NoSQL) DB
- Transactions are less common on NoSQL DBs because **coordination is slow** across many nodes.  
- A transaction-like behavior can be implemented by **locking** the key.  
- All replicas must agree to the lock before allowing the write.  

---

### How to Implement a Distributed Lock?

1. **Centralized Lock Service**  
   - Use a single coordination service to manage locks.  
   - Examples: **ZooKeeper**, **etcd**, **Consul**.  
   - Clients request a lock from the service → the service grants it if available.  

2. **Database-based Locking**  
   - Use the underlying database to simulate locks.  
   - Example: In Redis, use `SET key value NX PX <timeout>` to create a lock.  
   - Must handle lock expiry and renewal carefully (avoid deadlocks).  
   - **Redlock algorithm** (by Redis) improves reliability using multiple Redis instances.  

3. **Quorum-based Locking**  
   - Lock is considered acquired if a majority (`> N/2`) of nodes agree.  
   - Ensures fault tolerance if some nodes are down.  
   - Similar to quorum reads/writes (`R + W > N`) in distributed databases.  

4. **Leases with Expiration**  
   - Instead of permanent locks, use **time-limited leases**.  
   - If the client crashes, the lock will eventually expire, avoiding deadlock.  

---

### Throughput / Scaling Limitations

---

#### SQL Relational Database
- **Write bottleneck**:  
  - All writes must go to the **primary** node.  
  - This limits throughput since a single machine becomes the bottleneck.  
- **Read scaling**:  
  - Read-replicas can increase read throughput.  
  - However, replication introduces **delay/lag**, so replicas may return stale data.  
- **Sharding**:  
  - Can help with write scaling, but requires manual partitioning and complicates queries (especially JOINs).  

---

#### NoSQL and Scalable Stores
Many modern databases and storage systems use **data partitioning** (often via hashing or consistent hashing) to scale horizontally:  

- **Column-oriented DB** (e.g., Cassandra, HBase)  
  - Data distributed across nodes by partition key.  
  - Scales writes and reads horizontally.  

- **Search Engines** (e.g., Elasticsearch, Solr)  
  - Indexes are **sharded** across multiple nodes.  
  - Queries are distributed, results merged.  

- **Document Stores** (e.g., MongoDB, CouchDB)  
  - Documents distributed across shards by key.  
  - Provides horizontal scalability.  

- **Distributed Cache** (e.g., Redis Cluster, Memcached)  
  - Keys hashed across multiple nodes.  
  - Enables linear scalability for cache reads/writes.  

- **Cloud Object Stores** (e.g., Amazon S3, GCS, Azure Blob)  
  - Objects stored in a distributed manner with hashing + replication.  
  - Effectively infinite scaling in throughput and capacity.  

- **Cluster File Systems** (e.g., HDFS, Ceph, Lustre)  
  - Files split into blocks distributed across many nodes.  
  - Provides fault tolerance and high throughput for big data workloads.  

---

#### Networked Filesystem vs. RAID
- **Networked Filesystem** (e.g., NFS)  
  - **One machine** provides storage, multiple clients access it over a network.  
  - Scaling limited by the performance of the single server.  

- **RAID (Redundant Array of Independent Disks)**  
  - **One machine, many disks**.  
  - Improves throughput and reliability via striping, mirroring, or parity.  
  - Scaling limited by the controller and the single machine boundary.  

---

### OLTP (Online Transaction Processing) & OLAP (Online Analytical Processing)

---

#### OLTP – Online Transaction Processing
- **Purpose**: Manage day-to-day transactional data.  
- **Characteristics**:  
  - Many short, simple queries (INSERT, UPDATE, DELETE).  
  - Handles large numbers of concurrent users.  
  - Requires **ACID compliance** for correctness.  
- **Schema**: Highly normalized to reduce redundancy and maintain integrity.  
- **Workload Example**:  
  - E-commerce order system.  
  - Banking transactions.  
  - Reservation systems.  

---

#### OLAP – Online Analytical Processing
- **Purpose**: Analyze large volumes of historical/aggregated data.  
- **Characteristics**:  
  - Complex queries with aggregations, joins, and scans.  
  - Few concurrent users, but queries are computationally intensive.  
  - Focused on **read-heavy workloads** and multidimensional analysis.  
- **Schema**: Often denormalized for query efficiency (star schema, snowflake schema).  
- **Workload Example**:  
  - Business intelligence dashboards.  
  - Data warehousing queries.  
  - Trend and pattern analysis.  

---

#### Key Differences

| Feature              | OLTP                                | OLAP                                   |
|----------------------|-------------------------------------|----------------------------------------|
| **Goal**             | Real-time transactions              | Historical data analysis                |
| **Queries**          | Short, simple, frequent             | Long, complex, analytical               |
| **Data**             | Current, operational                | Historical, aggregated                  |
| **Users**            | Thousands of concurrent users       | Dozens of analysts/data scientists      |
| **Schema**           | Normalized (3NF)                    | Denormalized (Star/Snowflake)           |
| **Performance**      | Fast response for single records    | Fast scanning/aggregation of large sets |
| **Examples**         | ATM withdrawal, online purchase     | Sales forecasting, customer segmentation |

---

**Summary**:  
- **OLTP** = optimize for **fast, reliable transactions** (operational systems).  
- **OLAP** = optimize for **complex analytics on big data** (decision-making systems).  

---

### Distributed Data Store Comparison

---

#### MongoDB
- **Type**: JSON document store.  
- **Strengths**:  
  - Schema-less, flexible for evolving data structures.  
  - Optimized for frequent **document updates**.  
  - Supports **replication** and **sharding** for scalability.  
  - Can maintain **change history** (via versioning or separate collections).  
- **Best use cases**:  
  - Content management systems.  
  - User profiles with dynamic fields.  
  - Applications needing flexible schema design.  

---

#### Elasticsearch
- **Type**: JSON document store + distributed search/analytics engine.  
- **Strengths**:  
  - Stores documents and builds an **inverted index** → maps words to their locations in documents.  
  - Optimized for **full-text search** and complex queries.  
  - Supports aggregations, filtering, and near real-time search.  
  - Scales horizontally with sharding and replication.  
- **Best use cases**:  
  - Log and event analytics (ELK/Elastic stack).  
  - Full-text search in applications (e.g., e-commerce, websites).  
  - Monitoring, observability, and analytics dashboards.  

---

#### Cassandra (2D Key-Value Store / Wide-Column Store)
- **Data model**:  
  - Each **row** is identified by a **primary key**.  
  - Each row can have a dynamic set of **columns** (key-value pairs).  
  - Effectively, it’s a **map of maps** (row key → {column key → value}).  
- **Strengths**:  
  - Designed for **high write throughput** and **linear scalability**.  
  - Fault-tolerant with replication across multiple data centers.  
  - Tunable consistency: developers can choose between strong vs eventual consistency (`R + W > N` model).  
- **Limitations**:  
  - Not ideal for complex queries or ad-hoc joins.  
  - Query patterns must be known in advance and optimized via schema design.  
- **Best use cases**:  
  - Time-series data.  
  - IoT sensor data ingestion.  
  - Applications needing high availability across multiple regions.  

![Cassandra Schema Example](https://www.researchgate.net/publication/301630614/figure/fig5/AS:628782226497538@1526924773756/Data-schema-of-bridge-information-model-on-Apache-Cassandra.png)

---

#### Redis (In-Memory Key-Value Store)
- Data stored in **RAM** → ultra-low latency.  
- Supports strings, hashes, lists, sets, sorted sets.  
- Can act as **cache** or **ephemeral DB**.  
- Expiration policies for items.  

---

### Distributed Caches
- Examples: Redis, Memcached, ElastiCache, Riak.  
- Store data in **RAM across nodes**.  
- Provide **linear scalability** for reads/writes.  

**Comparison**:
- **NoSQL DB** → persistent, disk + RAM, scale is the goal.  
- **Distributed Cache** → ephemeral, RAM-based, expiration common.  
- **CDN** → caches common HTTP responses globally.  

---

### Hadoop Distributed File System (HDFS)
- Designed for **big data analytics**.  
- Moves computation **to where the data is**, instead of moving huge datasets across the network.  
- Splits files into blocks, distributed across commodity hardware.  
- Fault tolerance via replication (default 3 copies).  
- Backbone of Hadoop ecosystem (MapReduce, Spark).  
