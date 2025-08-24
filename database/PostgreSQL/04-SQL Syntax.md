# SQL Syntax

## Lexical Structure

### Command Terminator
- **Semicolon (;)**
  - Terminates an SQL command.
  - Cannot appear inside a command, except in:
    - A string constant
    - A quoted identifier

---

### Parameters & Identifiers
- **Dollar sign ($)**
  - `$` + digits:
    - Represents a **positional parameter** in function definitions or prepared statements.
  - In other contexts, `$` can appear in:
    - Identifiers
    - Dollar-quoted string constants

---

### Grouping & Precedence
- **Parentheses ( )**
  - Group expressions and enforce precedence.
  - Sometimes required as part of fixed SQL syntax.

---

### Arrays
- **Brackets [ ]**
  - Used to select **elements** from an array.
- **Colon (:)**
  - Used to select **slices** from arrays
  - In some SQL dialects (e.g., Embedded SQL), used to prefix variable names.

---

### Lists
- **Comma (, )**
  - Separates elements in a list within SQL constructs.

---

### Wildcards
- **Asterisk (*)**
  - Represents **all fields** of a table row or composite value.
  - In aggregate functions (e.g., `COUNT(*)`), denotes the aggregate has no explicit parameter.

---

### Names & Constants
- **Period (.)**
  - Used in:
    - Numeric constants (e.g., 3.14)
    - Separating schema, table, and column names (e.g., schema.table.column)
