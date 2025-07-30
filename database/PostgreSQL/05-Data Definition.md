# Data Definition

> **Note:** When reading a table, the rows appear in an *unspecified order*  
> unless sorting is explicitly requested using an `ORDER BY` clause.

## Table Basics

To remove a table from the database:

```sql 
DROP TABLE table;
```

However, if the table does not exist, this command will result in an error.
To safely drop a table only if it exists, use:
```sql
DROP TABLE IF EXISTS
```

## Identity Columns

- An identity column is a special column that is generated automatically from an implicit sequence. 
- An identity column is automatically marked as NOT NULL, 
- **Important:** Identity columns don't guarantee uniqueness, you must enforce uniqueness using `PRIMARY KEY` or `UNIQUE`.


### Behavior Comparison

#### SERIAL: You can override the value in insert:

```sql
INSERT INTO table (id, name) VALUES (5, 'test');
```

#### GENERATED ALWAYS: You cannot override unless you explicitly use:

```sql
INSERT INTO table (id, name) 
OVERRIDING SYSTEM VALUE 
VALUES (5, 'test');
```

This prevents accidental ID manipulation and protects integrity.

## Generated Columns

Generated columns are special table columns that are **automatically computed** from other columns in the same row.

### Types of Generated Columns

### 1. Stored

- Computed **when written** (during `INSERT` or `UPDATE`)
- **Consumes storage** like a normal column
- Conceptually similar to a **view**, but stored physically
- **PostgreSQL currently only supports this type**

### 2. Virtual *(not supported in PostgreSQL)*

- Computed **on read**
- **Does not consume storage**
- Conceptually similar to a **materialized view**

#### Syntax Example

```sql
CREATE TABLE people (
    ...,
    height_cm NUMERIC,
    height_in NUMERIC GENERATED ALWAYS AS (height_cm / 2.54) STORED
);
```

- The keyword STORED must be specified when defining a generated column in PostgreSQL.

## Rules and Restrictions

- Generation expression must use immutable functions only

- Generation expression cannot:

    - Use subqueries

    - Reference other generated columns

    - Reference system columns (except tableoid)

- A generated column cannot:

    - Have a default value

    - Be an identity column

    - Be part of a partition key

### Inheritance and Partitioning

- If a parent column is generated, the child must also be generated

    - Child may use a different expression

- If a parent column is not generated, the child must not be generated

- In CREATE TABLE ... INHERITS or ... PARTITION OF:

    - Omitting GENERATED in the child copies it from the parent

- ALTER TABLE ... INHERIT or ALTER TABLE ... ATTACH PARTITION:

    - Requires matching generation status (generated vs. not generated)

    - Does not require matching generation expressions

- In multiple inheritance:

    - All parents must agree on the generated status

    - If expressions differ, the child must explicitly specify its expression

### Additional Considerations

- Access Privileges
Generated columns maintain separate privileges from their base columns.
You can grant read access on the generated column without exposing the base columns.

- Triggers

    - Computation occurs after BEFORE triggers

    - Changes to base columns in BEFORE triggers are reflected in generated columns

    - Cannot reference generated columns inside BEFORE triggers

- Logical Replication

    - Generated columns are excluded from logical replication

    - Cannot be listed in CREATE PUBLICATION
