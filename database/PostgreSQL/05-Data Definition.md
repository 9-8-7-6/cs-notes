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

