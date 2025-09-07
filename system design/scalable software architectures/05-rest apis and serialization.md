# REST APIs and Data Serialization

## HTTP

### Method
* **GET**
* **POST**
* **PUT**
* **DELETE**
* **HEAD**: Fetch headers without the body

### Response Output
* Status code
  * 200 OK
  * 301 Moved Permanently
  * 403 Forbidden
  * 404 Not Found
  * 500 Internal Server Error
* Headers
* Body
  * Usually JSON encoded

---

## Idempotent

**Definition:** 
An operation is *idempotent* if executing it multiple times has the **same effect** as executing it once, that is resource stay the same.

* **POST is Not idempotent** – creating a new resource each time produces different results (e.g., multiple entries).

**Example:**  
- `DELETE /users/123` → First call removes the user, subsequent calls have no further effect.  
- `DELETE /user/[user-id]/feed/posts/lastest`

* Http DELETE should be idempotent, so it should be identified uniquely

---

## RESTful Principles

* Url paths represent **resources** (data or object in the system)
* **GET** reads data
* **PUT/POST** create or modify data
* **DELETE** deletes data
* Prefer **using HTTP verbs in methods** rather than embedding verbs in the path.  

---

## Serialization

### References make serialization non-trivial without Circular references

> Serialization is converting complex in-memory objects into a format suitable for **storage or transmission** (e.g., JSON, XML, Protocol Buffers).

### Challenges
- **References and Circular Dependencies**  
  - Objects may reference each other (A → B, B → A), making naïve serialization impossible.
  - This can cause infinite loops or duplicated data.

### Solutions
1. **Serialize with References**  
   - Replace object references with unique identifiers (IDs).
   - Example: Instead of embedding a full `User` object in a `Post`, only store `user_id`.

2. **Flattening / Breaking Cycles**  
   - Redesign object relationships to avoid direct cycles.
   - Example: Store parent references but not child references, or vice versa.

3. **Specialized Formats**  
   - Use formats that support references natively (e.g., YAML anchors, certain binary protocols).

### Trade-offs
- **Producer (server)**: Must resolve and assign IDs for referenced objects before serialization.  
- **Consumer (client)**: May need to perform additional fetches or lookups to fully reconstruct the data.  

