# Computer Abstractions and Technology

## Bit
A **bit** is the most fundamental unit of digital information, representing either **0 (low)** or **1 (high)**.

### Digital Logic Levels
- Lower than threshold voltage represents **Low (0)**.  
- Higher than threshold voltage represents **High (1)**.  
These voltage levels are interpreted by transistors acting as electronic switches.

---

## Transistor as a Switch
- A transistor consists of three parts: **Source**, **Gate**, and **Drain**.  
- Modern computers use transistors to implement **logic gates** and **memory circuits**.  
- A transistor controls the flow of electric current, acting as a tiny **on/off switch**.

### Two Main Types of Transistors
- **NMOS (N-type Metal-Oxide-Semiconductor)**  
  - Made from n-type silicon that contains more free **electrons** (negative charge carriers).  
  - Conducts when the voltage at the gate is **high**.  
  - Passes strong 0 but weak 1.

- **PMOS (P-type Metal-Oxide-Semiconductor)**  
  - Made from p-type silicon that contains more **holes** (positive charge carriers).  
  - Conducts when the voltage at the gate is **low**.  
  - Passes strong 1 but weak 0.

![NMOS and PMOS](https://www.mks.com/mam/celum/celum_assets/Figure_11-Semiconductor_Handbook_800w.jpg)

---

## CMOS Technology
Most modern chips use **CMOS (Complementary Metal-Oxide-Semiconductor)** technology,  
which combines NMOS and PMOS transistors to form energy-efficient logic gates.

When the input is **high (1)**, NMOS conducts and PMOS is turned off, resulting in a **low (0)** output.  
When the input is **low (0)**, PMOS conducts and NMOS is turned off, resulting in a **high (1)** output.  
This design allows for **very low power consumption** and **high switching speed**.

---

## Working Principle of a Transistor
1. When a **positive voltage** is applied to the gate, electrons in the **p-type silicon** are attracted to the area under the gate, forming an **electron channel** between the source and the drain.  
2. When a **positive voltage** is applied to the drain, electrons flow from the source to the drain. In this state, the transistor is **on**.  
3. When the **voltage at the gate** is removed, the channel disappears and current no longer flows. The transistor is **off**.

---
## CMOS NAND Gate
In a CMOS NAND gate,
- The PMOS transistors are connected in parallel at the top (connected to VDD).
- The NMOS transistors are connected in series at the bottom (connected to GND).

![CMOS NAND](https://www.ic-components.com/upfile/images/77/20240703134504908.png)

---