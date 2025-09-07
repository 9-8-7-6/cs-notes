# Microservices

---

## Monolithic

Each instance can handle all requests by itself, enabling parallel processing.

### Advantages
- Easy to **build**, **deploy**, **test**, and **coordinate**
- Simpler debugging (all code in one place)

### Disadvantages
- Can create **bottlenecks** easily
- Requires lots of **coordination/merging** for teams
- **Large redeployment** procedure for every new function
- Tied to **one programming language**, **build system**, and **runtime environment**

---

## Microservices

**Service-Oriented Architecture (SOA):**  
The system is split into many small, independent services that communicate via the **network**.  
Each service is treated as a **black box** by the rest of the system.

### Advantages
- Clear API boundaries between services  
- Teams can develop, test, and deploy **in parallel**  
- Independent scaling of services

### Disadvantages
- Harder to **trace code and debug** because the system spans many applications
- **Transactions are difficult** since data may be distributed across multiple databases
- Requires more effort in **infrastructure, monitoring, and communication**

---

## Team Collaboration in Microservices

1. **Organize** the system into multiple services and codebases.  
2. **Plan** the network-level APIs for each service.  
3. **Allocate engineers** to own and manage each service.  
4. Use **mocks/stubs** for services that are under construction to allow parallel development and testing.
