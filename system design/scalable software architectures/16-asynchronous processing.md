# Asynchronous Processing

---

## Asynchronous Response
- Sometimes it's acceptable to **acknowledge a request immediately** and complete the work later.  
- **Pros**:  
  - Client can move on quickly without waiting for processing.  
- **Cons**:  
  - Client does not immediately know whether the request **succeeded** or **failed**.  

---

## Synchronous vs. Asynchronous

- **Synchronous style**  
  - **Request**: Deliver an email.  
  - **Response**: Delivery acknowledged (immediate confirmation of completion).  

- **Asynchronous style**  
  - **Request**: Send an email.  
  - **Response**: Attempt acknowledged (work will be processed later).  

---

## How to Let the Client Know When Work is Done

### Option 1: Request Record
- Server stores a **request record** in a database and returns a unique **request ID**.  
- When work is completed, the server updates the record in the DB.  
- Client can **poll** or query the server later with the request ID to check status.  

---

### Option 2: Callback to Client
- Client provides a **callback function (webhook)** endpoint.  
- Once processing is finished, the server makes a request to the client’s callback URL.  
- Client is notified automatically (push-based feedback).  

---

### Option 3: Side Channel for Feedback
- Use a **separate channel** (e.g., message queue, notification system, WebSocket).  
- Client subscribes to updates and receives status when the request completes.  
- Often used for long-running background jobs or streaming systems.  

---

## Message Queue

- If the client doesn’t care about the **response status**, it can just put the request on a **queue**.  
- Putting a message on a queue is like making an API request.  

### Queue Terminology
- **Producer**: pushes/publishes/produces messages.  
- **Consumer**: pulls/pops/consumes/subscribes to messages.  

- A message queue can be partitioned into **several virtual queues** by assigning a **topic** to each message.  

---

## Tradeoffs

- **Tightly coupled (synchronous) services**  
  - Simpler to design and build.  
  - Immediate error handling and feedback.  

- **Loosely coupled (asynchronous) services**  
  - Can be faster and more scalable.  
  - But:  
    - Failures may be ignored if response isn’t checked.  
    - Errors might only be logged in DB → harder to react to later.  
    - Errors may require delayed alerts/notifications to the user.  

---

## Decouping helps scaling
- Message queue can lead many producers and many consumers.


---

## Active vs. Passive Queues

Passive Queue:
- Stores messages until consumers request (poll) them.

Active Queue:
- Actively pushes messages out to subscribed consumers.
