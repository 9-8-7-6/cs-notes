# Proxies and Caches

## Proxies
> A proxy server is an intermediary router for requests

- A **load balancer** is a type of proxy that connects to many app servers.
- **Squid** is a caching proxy (storing recently used items for reuse).

## Cache
> Cache is data storage (most recently/frequently used data) to improve performance when accessing a large data store.

- The most common policy is **LRU** (Least Recently Used).

### Types of Caches

1. **Managed Cache**
    - Need to write code and manage the configuration
    - Example: Redis, Memcached

2. **Transparent Cache**
    - Don't need to write code and manage the configuration
    - Example: Squid caching proxy, CDNs, Database server


---

## Data writes cause cache to be out of date!

- Many clients can have their own caches.
- When data changes, old copies may be cached and returned to clients (e.g., a Wiki article is edited).

### Three basic solutions:
1. **Expire** cache entries after a certain TTL (time to live)
2. After writes, send new data or an invalidation message to all caches to create a **coherent cache** (but this adds performance overhead)
3. Avoid changing data in-place; instead, create new filenames or keys for new data entries (**versioned data**)
