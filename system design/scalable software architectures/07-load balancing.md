# Load Balancing
> A **load balancer** is a single point of contact for a service, distributing traffic across multiple servers to improve reliability, scalability, and availability.

---

## Basic Idea
- Make a **cluster of servers** look like one superior server.  
- Individual servers can be replaced or updated without affecting the overall service.  
- **Update Strategies**:
  - **Rolling Update**: Update servers **gradually**, keeping service running.  
  - **Synchronized Update**: All servers switch to the new version **at once**.  
    - Requires preparing a full-size duplicate cluster.
    - Expensive, but ensures consistency.  
- **Health Check**: Periodically send requests (e.g., HTTP ping).  
  - If a server fails, it is marked as unavailable and removed from the pool.

---

## Types of Local Load Balancers

### 1. Network Address Translation (NAT)
- Operates at the **TCP/IP layer**.  
- Forwards packets directly to backend servers.  
- **Pros**: Simple, low latency.  
- **Cons**: Limited flexibility (cannot modify application-level data).  

---

### 2. Reverse Proxy
- Operates at the **Application Layer (HTTP/HTTPS)**.  
- Examples: **Nginx**, **HAProxy**, **Apache HTTP Server**.  
- Additional features:  
  - **TLS/SSL termination** (offload encryption/decryption).  
  - **Caching** (e.g., Squid).  
  - **Compression** to reduce bandwidth.  
  - **Request rewriting** and routing (e.g., A/B testing).  

---

## Load Balancing Algorithms
1. **Round Robin**  
   - Each request is sent to the next server in order.  
   - Simple and fair if servers are equally capable.  

2. **Weighted Round Robin**  
   - Assigns weights based on server capacity.  
   - Stronger servers handle more requests.  

3. **Least Connections**  
   - Directs new requests to the server with the fewest active connections.  
   - Good for long-lived sessions.  

4. **IP Hash**  
   - Client IP determines which server receives the request.  
   - Ensures session persistence ("sticky sessions").  

---

## Content Delivery Network(CDN)
> Globally distributed web servers that cache responses for local clients

- CDN is just a distributed caching HTTP reverse proxy

- Edge Server are caching proxies