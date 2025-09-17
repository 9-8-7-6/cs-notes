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
