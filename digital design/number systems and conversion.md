# Introduction / Number Systems and Conversion

## Analog and Digital

An **analog signal** is **continuous**, meaning it has a value at every possible point in time, even when the change in time (ΔT) is very small.  
A **digital signal**, on the other hand, is **discrete** — it represents information using separate values, typically in binary form (0s and 1s).

Although the real world is analog, **digital systems are more reliable** and easier to process.  
Therefore, many modern systems **convert from analog to digital** for computation and control.

### Analog Characteristics
- Continuous signal  
- Infinite possible values  
- Sensitive to noise and distortion  
- Difficult to store or transmit accurately  

### Digital Characteristics
- Discrete signal  
- Limited number of values (usually 0 and 1)  
- Resistant to noise  
- Easy to store, process, and transmit  

Analog systems try to achieve **error-free precision**, but even small noise can lead to large errors.  
Digital systems, in contrast, **define a fixed maximum error** (called *quantization error*).  
The **more bits** used in the digital representation, the **higher the accuracy**.

### Signal Conversion
- **A/D Converter (Analog-to-Digital Converter):** Converts continuous analog signals into digital data.  
- **DSP (Digital Signal Processing):** Processes digital signals to extract, modify, or enhance information.  
- **D/A Converter (Digital-to-Analog Converter):** Converts digital data back into an analog signal.  

### Example: Voice Transmission
In a **phone call**, the analog voice signal is **sampled** — divided into discrete time intervals.  
Sampling allows the analog waveform to be represented digitally.  
If the sampling rate is high enough (dense sampling), the reconstructed signal closely matches the original analog voice.

---

## System Hierarchy

A digital system can be divided into **three levels**:

1. **System Level:**  
   Composed of functional modules such as the ALU, memory, and control unit.

2. **Logic Level:**  
   Built from logic gates (AND, OR, NOT, etc.) that define logical relationships.

3. **Circuit Level:**  
   Constructed using transistors, resistors, and other electronic components.

---

## Switching Circuit

A **switching circuit** represents logical states using electrical signals:

- **ON → 1**  
- **OFF → 0**

**Inputs:** S1, S2  
**Output:** V0  

The switches form a **switching network** that determines the output based on input conditions.

- If **S1 OR S2** is ON → Output = **1**  
- If **S1 AND S2** are OFF → Output = **0**

### Types of Switching Networks

- **Combinational Network:**  
  The output depends only on the current input values.

- **Sequential Network:**  
  The output depends on both the current input and the system’s previous state (it has **memory behavior**).

### Switch Implementation

A **switch** or **logic gate** can be **realized using transistors**, which act as controllable switches that conduct or block current based on the input signal.

---

## Number Systems and Conversion

### Binary Representation
- `0000` → 0  
- `0111` → 7  
- A binary number **starting with 1** indicates a **negative number** when signed representation is used.

### Sign and Magnitude
- The **most significant bit (MSB)** represents the **sign bit**, while the remaining bits represent the **magnitude**.  
  - `0` → Positive  
  - `1` → Negative  
- Example: `1001` → -1 (if 4-bit system)  
- Simple in concept but **difficult to implement in hardware** because it requires special handling for arithmetic operations.

### 1’s Complement
- Obtained by **inverting all bits** (0 ↔ 1).  
- Example:  
  - `0000` → 0  
  - `1111` → -0  
- Formula:  
  - `-N = (2^n - 1) - N`  
- Computed **bit by bit**.  
- Has **two representations of zero**: `0000` (+0) and `1111` (-0).

### 2’s Complement
- Obtained by **inverting all bits** (0 ↔ 1) and then **adding 1**.  
- Example:  
  - `0000` → 0  
  - `1111` → -1  
  - `1000` → -8 (in 4-bit system)  
- Formula:  
  - `-N = 2^n - N`  
- Computed **bit by bit**, then add 1.  
- Only **one representation of zero** and allows **simpler arithmetic operations**.
- Range from + 2^(n - 1) - 1 ~ - 2^(n - 1)

### Summary
- **2’s complement** is the most widely used representation for signed integers in modern digital systems because it simplifies hardware design and arithmetic logic.

---

### Addition

1. **Addition of two positive numbers, sum < 2^(n - 1)**  
   Example:  
   3 + 4 = 7  
   `0011 + 0100 = 0111`  
   No overflow occurs because the sum is within the representable range.

2. **Addition of two positive numbers, sum ≥ 2^(n - 1)**  
   Example:  
   5 + 6 = 11  
   `0101 + 0110 = 1011` → interpreted as `-5` in 4-bit 2’s complement.  
   This result is incorrect due to **overflow**.  
   The correct representation of 11 requires **5 bits including the sign bit**.

---

### Subtraction

Subtraction can be performed by **adding the two’s complement** of the subtrahend:

1. **A - B = A + (-B)**  
   Example:  
   5 - 6 = -1  
   `0101 + 1010 = 1111` → represents `-1`

2. **-A + B**  
   Example:  
   -5 + 6 = 1  
   `1011 + 0110 = (1)0001`  
   The carry bit (1) is **discarded**, which is equivalent to subtracting `2^n`.

If subtraction leads to overflow, the result cannot be represented correctly within `n` bits.

---

### Proof

To show that subtraction can cause overflow:

```
-A - B = (2^n - A) + (2^n - B)
= 2 * 2^n - (A + B)
≥ 2^n
```
Since the result exceeds the range representable by `n` bits, **overflow occurs**.

## Binary Code

1. **Binary-Coded Decimal (BCD) — 8-4-2-1 Code**  
   - Each **decimal digit (0–9)** is represented using **4 bits**.  
   - Commonly used for **input/output** operations where conversion between decimal and binary is required.  
   - Example:  
     - Decimal 9 → BCD `1001`  
     - Decimal 23 → BCD `0010 0011`  

2. **6-3-1-1 Code**  
   - A **weighted code** used in some digital display systems.  
   - Each bit has a weight of 6, 3, 1, and 1 respectively.  
   - Used for error detection and certain encoding applications.  

3. **Excess-3 Code (XS-3)**  
   - A **non-weighted code** derived from BCD by adding 3 (`0011`) to each decimal digit.  
   - Example:  
     - Decimal 0 → XS-3 `0011`  
     - Decimal 5 → XS-3 `1000`  
   - Often described as a **self-complementary code** because the 9’s complement of a number can be obtained directly by inverting all bits (pair complement property).
