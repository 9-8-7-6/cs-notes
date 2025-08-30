# Types of Scaling

## What's the difference between apps and **services**?

> Service runs as a permanent daemon on machine to listen and handle request from clients.

---

## What's **scalability**? Why is it difficult?

- Traditional -> Time Complexity
    - It assume: 
        1. One problem to solve
        2. One computer
        3. All operations having the same cost 

Service metrics are measure of work throughput:
- Requests/queries per second
- Concurrent user
- Monthly-active users

---

## Scaling Chanllenge

### Why is it difficult to make services big, even if money ain't a thing?

- Programs runs on one machine with limit speed.
- Coordinating multiple machine could be difficult.
- Sharing data among machines is dificult.
- More machines means higher probability to fail.
- User distributed worldwide lead to high communication **latency**
- Services must trust each other but also guard against attackers.
- Software updates must be deployed without downtime.

---

## Vertical Scaling
> Upgrade machine by improving machine resource.
1. Number of CPU cores.
2. Speed of each CPU core.
3. Less competing process running on the same machine so resource is not sharing.
4. Amount of memory.
5. Types of disk.
6. Number of disks(parallel access)
7. Network connectivity.
8. GPUs, TPUs(special-purpose accelerators)

--- 