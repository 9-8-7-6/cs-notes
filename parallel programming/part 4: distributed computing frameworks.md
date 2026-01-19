# Distributed Computing Frameworks

## Hadoop

### Big Data
Extracting values from an immense volume, variety and velocity of data, in context, beyond what was perviously possible.

#### Problems
*   Volume: data might scale from terabytes to petabytes to zetabytes.
*   Variety: Manage the complexity of data in many different structures, ranging from relational to logs to raw text.
*   Velocity: streaming data and large volume data movement. How fast to process the data.

---

### MapReduce
Process PB of data per data using datacenters.\
Program written in this functional style are automatically parallelized and executed on machines.\
Hadoop is the open source(JAVA) implemented by Yahoo.\
MapReduce = programming model + implementation + system architecture.\

### Large-Data Problem
*   Process a very large number of records in parallel.
*   Map: Transform each record into intermediate key-value pairs.
*   Shuffle & Sort: Group intermediate results by key.
*   Reduce: Aggregate or summarize values for each key.
*   Generate final output.

### Hadoop Eco-system

### Hadoop Programming

## Spark