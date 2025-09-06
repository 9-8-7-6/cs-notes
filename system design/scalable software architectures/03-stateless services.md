# Stateless Services

* State equals memory here, determined by:
  1. Input request
  2. The code handling the request

## What is the main purpose of object-oriented programming?
* Group related data (memory/variables) and functions together in a class
* The **side effects (changes in state)** of these functions are limited to the data inside that class
* A class defines member functions whose side effects only affect a small, controlled set of variables

## Horizontally scaling Stateful vs Stateless code

* Stateless code (has no memory)
  * All copies give the same response
  * It doesn't matter which copy processes the request
  * Example: HTTP (single request)

* Stateful code (has memory)
  * Different copies process different states; they may give different responses for the exact same request
  * Example: SMTP (series of requests)

### Examples of Side Effects on Wikipedia

1. **Page Edit** might have side effects because the data is duplicated into several servers.
   * The database separates system state from stateless handlers by using a shared DB, effectively **pushing state down to a database**.

2. **Sign In** might have side effects on Wikipedia.
   * After signing in, all later responses will have a different page header (that is state).
   * How to avoid?
     * **Cookies** solve the problem by storing state data in the DB.
     * So the client and DB together keep the sign-in state.
