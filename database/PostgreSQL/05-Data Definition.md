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

### Constraints

A constraint is a rule defined on a column or a column restrict the data inserted or updated.

#### Check Constraints

- Check constraints allow you to specify the value in a certain column must satisfy a boolean expression

```PostgreSQL
CREATE TABLE products (
    product_no integer,
    name text,
    price numeric CHECK (price > 0)
);
```

- You can also give the constraint a separate name. This clarifies error messages and allows you to refer to the constraint when you need to change it.

```PostgreSQL
CREATE TABLE products (
    product_no integer,
    name text,
    price numeric CONSTRAINT positive_price CHECK (price > 0)
);
```

#### Limitations of Check Constraints in PostgreSQL
- Check constraints can only reference the current row.
    - You cannot compare values against other rows or tables.
    - While it might appear to work, it may lead to inconsistent data and restore failures after a database dump.
    - Example failure: rows are restored in an order that violates the constraint.
- Do not use CHECK for cross-row or cross-table logic.
Use these instead:
    - UNIQUE
    - EXCLUDE
    - FOREIGN KEY
- If you only need to check other rows once at insertion time, use a custom trigger instead.
Triggers are not enforced during a pg_dump restore, so they avoid related issues.
- PostgreSQL assumes CHECK conditions are immutable:
    - The result must always be the same for the same input row.
    - If the check uses a user-defined function, and you later change that function’s logic:
        - PostgreSQL will not re-validate existing rows.
        - This may cause dump/restore errors due to now-invalid data.

- Recommended process when changing function logic used in a CHECK constraint:

```PostgreSQL
ALTER TABLE your_table DROP CONSTRAINT your_check;
-- Modify the function logic here
ALTER TABLE your_table ADD CONSTRAINT your_check CHECK (...);
```
This ensures the constraint is re-evaluated across all rows.

#### Not-Null Constraints

> **NOT-NULL** constraint is equivalent to creating a **CHECK** but more efficient.

```PostgreSQL
CREATE TABLE products (
    product_no integer NOT NULL,
    name text NOT NULL,
    price numeric NOT NULL CHECK (price > 0)
);
```

#### Unique Constraints

> Data in column **only** is unique among all rows in the table.

```PostgreSQL
CREATE TABLE products (
    product_no integer,
    name text,
    price numeric,
    UNIQUE (product_no)
);
```

#### Primary Keys

> This requires values be both **unique** and **not null**

```PostgreSQL
CREATE TABLE products (
    product_no integer UNIQUE NOT NULL,
    name text,
    price numeric
);

CREATE TABLE products (
    product_no integer PRIMARY KEY,
    name text,
    price numeric
);
```

- Primary key will automatically create an unique B-tree index

#### Foreign Keys

> A foreign key is a column or a set of columns in one table that establishes a link to the primary key of another table, enforcing referential integrity between the two tables.

### System Columns

> Every table has several system columns that are implicitly defined by the system.

- tableoid
    - **tableoid** is a built-in system column that returns the OID of the table from which each row was read.
- xmin
    - The transaction ID (XID) of the transaction that inserted the row
- cmin
    - The command ID within the inserting transaction
- xmax
    - The transaction ID of the transaction that deleted or invalidated the row
- cmax
    - The command ID within the deleting transaction
- ctid
    - The physical location of the row within its table as a (block, offset) tuple.


### Modifying Tables

#### Add columns

> ALTER TABLE `products` ADD COLUMN `description` text;

> ALTER TABLE `products` ADD COLUMN description `text` CHECK (description <> '');

#### Remove columns

> ALTER TABLE `products` DROP COLUMN `description`;

#### Add constraints

> ALTER TABLE `products` ADD CHECK (name <> '');

#### Remove constraints

> ALTER TABLE products DROP CONSTRAINT some_name;

#### Change default values

> ALTER TABLE `products` ALTER COLUMN `price` SET DEFAULT `7.77`;

#### Change column data types

> ALTER TABLE products ALTER COLUMN price TYPE numeric(10,2);

#### Rename columns

> ALTER TABLE products RENAME COLUMN product_no TO product_number;

#### Rename tables

> ALTER TABLE products RENAME TO items;

### Privileges

#### Object is assigned to the role created it as owner normally.To allow other roles to use it, *privileges* must be granted.

> Assign a new owner

```sql
ALTER TABLE table_name OWNER TO new_owner;
```

> Assign privileges

```sql
GRANT UPDATE ON accounts TO joe;
```

> Revoke previously-granted privilege(Unto)

```sql
REVOKE ALL ON accounts FROM PUBLIC;
```

#### Available privileges
* SELECT
* INSERT
* UPDATE
* DELETE
* TRUNCATE
* REFERENCES
* TRIGGER
* CREATE
* CONNECT
* TEMPORARY
* EXECUTE
* USAGE
* SET
* ALTER SYSTEM
* MAINTAIN
