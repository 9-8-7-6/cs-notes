# Boolean Algebra

**Concept:**  
Boolean Algebra is the mathematical foundation for analyzing and designing digital logic circuits.  
Each variable can have two values:  
- `0` → False / Low / OFF  
- `1` → True / High / ON  

A switching network maps **inputs** to **outputs** using Boolean rules:
Input → Switching Network → Output


---

## Complement (NOT / Inverter)

**Function:** Reverses the input value.  
- `0 → 1`  
- `1 → 0`

**Symbol:**  
`x'` or `x̅`

**Logic Diagram:**  
![NOT Gate](https://signoffsemiconductors.com/wp-content/uploads/2021/11/g1-2.png)

---

## AND Operation

**Function:** Output is `1` only if all inputs are `1`.

**Symbol:**  
`x ⋅ y` or simply `xy`

**Logic Diagram:**  
![AND Gate](https://signoffsemiconductors.com/wp-content/uploads/2021/11/and_gate-2.png)

---

## OR (Inclusive OR)

**Function:** Output is `1` if any input is `1`.

**Symbol:**  
`x + y`

**Logic Diagram:**  
![OR Gate](https://signoffsemiconductors.com/wp-content/uploads/2021/11/or-1.png)

---

## Boolean Laws and Simplification Rules

### 1. Commutative Law
- **AND:** `xy = yx`  
- **OR:** `x + y = y + x`

### 2. Associative Law
- **AND:** `x(yz) = (xy)z = xyz`  
- **OR:** `(x + y) + z = x + (y + z) = x + y + z`

### 3. Distributive Law
- **AND over OR:** `x(y + z) = xy + xz`  
- **OR over AND:** `x + yz = (x + y)(x + z)`

---

## Common Simplifications

| Expression | Simplified Form | Note |
|-------------|-----------------|------|
| `(x + y)(x + z)` | `x + yz` | Distributive form |
| `xy + xy'` | `x` | Complement term elimination |
| `(x + y)(x + y')` | `x` | Common variable dominates |
| `x + xy` | `x` | Absorption law |
| `x(x + y)` | `x` | Idempotent simplification |
| `(x + y')'` | `xy` | De Morgan’s Law (negated OR) |
| `xy' + y` | `x + y` | Consensus theorem |

---

### Intuitive Notes
- When all terms share a common variable `x`, the **simpler term dominates**.  
  Example:  
  `x + xy = x(1 + y) = x`
- `x(1 + y)` simplifies to `x` because `(1 + y)` is always `1`.
- Boolean algebra often relies on finding **dominant variables** to simplify logic.

---
