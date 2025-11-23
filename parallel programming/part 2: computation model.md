# Computation Model

## Embarrassingly Parallel

A computation that can be divided into a number of **completely independent tasks**.

### 1. Image Transformation
    - Shifting x' = x + deltax, y' = y + deltay
    - Scaling x' = Sx * x, y' = Sy * y
    - Rotation x' = x * cos(theta) + y * sin(theta), y' = -x * sin(theta) + y * cos(theta)
---

### 2. Image Region Partitioning

An example of **Master-Slave** communication logic.

```c
// --- Master Process ---
for(i = 0, row = 0; i < 48; i++, row += 10) {
    send(row, Pi);
}

// Initialize temporary map
for(i = 0; i < 480; i++) {
    for(j = 0; j < 640; j++) {
        temp_map[i][j] = 0;
    }
}

// Receive calculated pixels
for(i = 0; i < (480 * 640); i++) {
    recv(oldrow, oldcol, newrow, newcol, Pany);
    
    // Boundary Check
    if (!((newrow < 0) || (newrow >= 480) || (newcol < 0) || (newcol >= 640))) {
        temp_map[newrow][newcol] = map[oldrow][oldcol];
    }
}

// Update original map
for(i = 0; i < 480; i++) {
    for(j = 0; j < 640; j++) {
        map[i][j] = temp_map[i][j];
    }
}

// --- Slave Process ---
recv(row, Pmaster);
for(oldrow = row; oldrow < (row + 10); oldrow++) {
    for(oldcol = 0; oldcol < 640; oldcol++) {
        newrow = oldrow + delta_x;
        newcol = oldcol + delta_y;
        send(oldrow, oldcol, newrow, newcol, Pmaster);
    }
}
```

---

### 3. Mandelbrot Set

The Mandelbrot set is a set of complex numbers that are quasi-stable (they do not diverge to infinity under iteration).

**Basic Formula:**
$$ Z_0 = C $$
$$ Z_{k+1} = Z_k^2 + C $$

Where:
*   $C = a + bi$ (a complex number representing the pixel position)
*   $Z_{k+1}$ is the $(k+1)^{th}$ iteration.
*   **Divergence Condition:** Once $|Z_k| > 2$, the value will increase forever.

---

#### Mathematical Derivation

To implement this in code, we separate the real and imaginary parts.
Let $C = C_{real} + C_{imag}i$ and $Z_k = Z_{real} + Z_{imag}i$.

Substituting into $Z_{k+1} = Z_k^2 + C$:

$$
\begin{aligned}
Z_{k+1} &= (Z_{real} + Z_{imag}i)^2 + (C_{real} + C_{imag}i) \\
        &= (Z_{real}^2 - Z_{imag}^2 + 2Z_{real}Z_{imag}i) + (C_{real} + C_{imag}i)
\end{aligned}
$$

Grouping the Real and Imaginary parts gives the update rules for the next iteration:

$$
\begin{cases}
Z_{real\_next} = Z_{real}^2 - Z_{imag}^2 + C_{real} \\
Z_{imag\_next} = 2 \cdot Z_{real} \cdot Z_{imag} + C_{imag}
\end{cases}
$$

---

#### C Implementation

This program generates the Mandelbrot set in **PPM (Portable Pixel Map)** format.

```c
#include <stdio.h>

typedef struct {
    float imag;
    float real;
} complex;

/**
 * Output color pixel based on iteration count.
 * Format: PPM (R G B)
 */
void display(int x, int y, int count) {
    int r, g, b;
    
    if (count == 256) {
        // Inner of Mandelbrot set (stable), set it as black
        r = 0; g = 0; b = 0;
    } else {
        r = count % 256;        // red
        g = (count * 5) % 256;  // green
        b = (count * 13) % 256; // blue
    }

    printf("%d %d %d ", r, g, b);
}

/**
 * Calculate the number of iterations before divergence.
 */
int cal_pixel(complex c) {
    int count = 0;
    int max = 256;
    float z_real = 0; 
    float z_imag = 0;
    float z_real2 = 0;
    float z_imag2 = 0;
    
    // Check for divergence: |Z|^2 < 4.0 (equivalent to |Z| < 2.0)
    while((z_real2 + z_imag2 < 4.0) && (count < max)) {
        // Z_imag_next = 2 * Zr * Zi + Ci
        z_imag = (2 * z_real * z_imag) + c.imag;
        
        // Z_real_next = Zr^2 - Zi^2 + Cr
        z_real = z_real2 - z_imag2 + c.real;
        
        // Update squares for the next iteration and distance check
        z_real2 = z_real * z_real;
        z_imag2 = z_imag * z_imag;
        
        count++;
    }
    return count;
}

int main() {
    int screen_width = 800;
    int screen_height = 600;

    // PPM Header
    printf("P3\n%d %d\n255\n", screen_width, screen_height);

    // Mandelbrot's coordinate range
    float min_r = -2.5, max_r = 1.5;
    float min_i = -2.0, max_i = 2.0;

    float dx = (max_r - min_r) / screen_width;
    float dy = (max_i - min_i) / screen_height;

    complex c;
    int color;

    for(int py = 0; py < screen_height; py++) {
        for(int px = 0; px < screen_width; px++) {
            // Map screen coordinates to complex plane coordinates
            c.real = min_r + px * dx;
            c.imag = min_i + py * dy;

            color = cal_pixel(c);

            display(px, py, color); 
        }
    }
    return 0;
}
```

#### Fractal
- An object that displays **self-similarity** (self-repeating) at various scales.
- Small-scale details are similar to the large-scale characteristics.

---

### Load-balancing & Termination

Issues arising in parallel computation models (like the Mandelbrot set generation) where task execution times vary.

#### **Load-balancing**
> Used to distribute workloads evenly across processors to ensure that no single processor is overwhelmed while others are idle, thereby maximizing overall speed and efficiency.

---

### 1. Static Load-Balancing
**Definition:** Pre-determine assignment between tasks and processes before execution starts.

**Algorithms:**
1.  **Round Robin Algorithm**: Assigns tasks sequentially in a circular order.
2.  **Randomized Algorithm**: Assigns tasks randomly to processes.
3.  **Recursive Bisection**: Recursively divides the problem into sub-problems of equal computational effort.

**Drawbacks:**
*   It is very difficult to accurately estimate the execution time of tasks beforehand.
*   Communication delays vary under different circumstances, which can disrupt the pre-planned schedule.

---

### 2. Dynamic Load-Balancing
**Definition:** Assign tasks to processes **during** the execution.

*   **Pros & Cons:** It incurs additional overhead during execution (due to communication and monitoring), but it is generally more effective than static load balancing, especially when workload is uneven.

**Approaches:**

#### 1. Centralized Work Pool
*   **Also known as:** Work Pool / Processor Farm.
*   **Usage:** Particularly useful when tasks require different amounts of execution time.
*   **Workflow:**
    1.  Master sends task to Slave.
    2.  Slave returns result & requests the next task.
    3.  Master sends termination signal when empty.

#### 2. Decentralized Work Pool
*   Tasks are distributed without a single central coordinator, reducing bottlenecks but increasing complexity.
*   The master divides the work pool into parts to each of the "mini-masters".
*   Each mini-master controls one group of slaves.

#### 3. Fully Distributed Work Pool
*   Workload balancing is managed cooperatively by all processors.
*   Processes have or generate their own tasks.
*   Tasks may be transferred among processes.
*   Processes make their own local decision.

1. Receier-initiated method(Receiver has lighter load)
    *   Request tasks from heavy loaded processes.
    *   More suitable for heavy loaded system.
2. Sender-initiated method(Sender has higher load)
    *   Send tasks to light loaded processes.
    *   More suitable for light light loaded system.

#### **Termination Detection**
  > The mechanism to determine when the entire computation has successfully finished, especially in asynchronous or distributed systems where processes may not , or hard to know the global state.

## Divide-and-Conquer Pipelined Computations

## Synchronous Computations
