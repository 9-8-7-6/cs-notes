# Distributed Computing Frameworks

## Hadoop

### Big Data

Extracting value from an immense **volume**, **variety**, and **velocity** of data, in context, beyond what was previously possible.

### Big Data Challenges (3Vs)

- **Volume**  
  Data can scale from terabytes (TB) to petabytes (PB) to zettabytes (ZB).

- **Variety**  
  Managing diverse data structures such as relational data, logs, and raw text.

- **Velocity**  
  Handling streaming data and large-volume data movement efficiently.

---

### MapReduce

A framework for processing petabytes of data across distributed datacenters.

- Functional-style programming model  
- Automatically parallelized and executed on clusters  
- Hadoop is the open-source Java implementation  
- MapReduce = Programming Model + Implementation + System Architecture

### Large-Data Processing Model

- **Map**: Transform records into intermediate key-value pairs  
- **Shuffle & Sort**: Group intermediate results by key  
- **Reduce**: Aggregate values for each key  
- **Output**: Generate final results

#### Example: Word Count

**Map**
```
    Map(String docid, String text):
    for each word w in text:
    Emit(w, 1)
```

**Reduce**

```
Reduce(String term, Iterator<int> values):
sum = 0
for each v in values:
sum += v
Emit(term, sum)
```

### What Hadoop Handles

- Task scheduling  
- Data distribution  
- Synchronization  
- Fault tolerance  
- Runs on a distributed file system (HDFS)

---

### Distributed File System

### Hadoop Eco-system

### Hadoop Programming

## Spark