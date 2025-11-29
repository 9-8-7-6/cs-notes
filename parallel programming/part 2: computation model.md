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
*   $Z_0 = C$, 
$Z_{k+1} = Z_k^2 + C$

Where:
*   $C = a + bi$ (a complex number representing the pixel position)
*   $Z_{k+1}$ is the $(k+1)^{th}$ iteration.
*   **Divergence Condition:** Once $|Z_k| > 2$, the value will increase forever.

---

#### Mathematical Derivation

To implement this in code, we separate the real and imaginary parts.
Let $C = C_{real} + C_{imag}i$ and $Z_k = Z_{real} + Z_{imag}i$.

Substituting into $Z_{k+1} = Z_k^2 + C$:

$
\begin{aligned}
Z_{k+1} &= (Z_{real} + Z_{imag}i)^2 + (C_{real} + C_{imag}i) \\
        &= (Z_{real}^2 - Z_{imag}^2 + 2Z_{real}Z_{imag}i) + (C_{real} + C_{imag}i)
\end{aligned}
$

Grouping the Real and Imaginary parts gives the update rules for the next iteration:

$
\begin{cases}
Z_{real\_next} = Z_{real}^2 - Z_{imag}^2 + C_{real} \\
Z_{imag\_next} = 2 \cdot Z_{real} \cdot Z_{imag} + C_{imag}
\end{cases}
$

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
> The mechanism to determine when the entire computation has successfully finished, especially in asynchronous or distributed systems where processes may not have access to, or find it hard to determine, the global state.

---

##### 1. Single-Pass Ring Termination Algorithm
*   **Precondition:** Must assume processes can **NOT** be re-activated once they terminate.
*   **Workflow:**
    1.  When **P0** terminates, it generates a `token` and passes it to the next process **P1**.
    2.  When **Pi** receives the `token`:
        *   It waits for its own termination.
        *   Once terminated, it passes the `token` to the next process ($P_{i+1}$).
    3.  When **P0** receives the `token` back, it confirms that all processes have finished, and a global termination message can be sent.

##### 2. Dual-Pass Ring Termination Algorithm
*   **Feature:**
    It handles cases where processes **may be re-activated** (e.g., an idle process later receives a delayed message).

*   **Mechanism (Dijkstra's Token Coloring):**
    The algorithm uses a **two-pass token ring** with a **coloring scheme** to detect in-transit messages and reactivation.
    *   **Process Color:** A process may turn the token Black if it sends a message to a lower-numbered process in the ring, meaning that process might be reactivated later.
    *   **Token Color propagation:** The token becomes Black if any process marks it Black during its circulation.
    *   **Two-pass logic:**: 
        *   **Pass 1:** Token makes a full loop to check whether any process may still trigger reactivation (Black indicates possible in-transit messages).
        *   **Pass 2:** If Pass 1 ends with a White token, a second pass confirms that the system is stable and no delayed messages remain.
    *   **Termination Rule:** Global termination is confirmed **only if the token returns to P0 White after the second pass.**
    If the token returns **Black**, another two-pass cycle is started.

## Divide-and-Conquer Pipelined Computations
> Recursively divide a problem into sub-problems of the same form as the larger problem.

### Sorting Algorithms
> Re-arranging a list of numbers into increasing (non-decreasing) order. This is a common and critical operation in large data processing.

**Performance Goal:**
*   **Sequential:** $O(n \log n)$ is typically the best average case.
*   **Parallel (Ideal):** With $n$ processors, the goal is $\frac{n \log n}{n} = O(\log n)$.
*   **Reality:** While theoretically obtainable, the **constant hidden in the order notation is extremely large**, making it difficult to achieve perfect scaling in practice.

---

#### 1. Bucket Sort
**Concept:**
*   The range of numbers is divided into $m$ equal regions (buckets).
*   One bucket is assigned to each region.
*   Items are distributed to buckets, then each bucket is sorted sequentially.
*   **Assumption:** Works best when numbers are **uniformly distributed** (workload is balanced).

```c
/**
 * MPI Bucket Sort
 * Compile: mpicc bucket_sort.c -o bucket_sort
 * Run:     mpirun -np 4 ./bucket_sort
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define DATA_SIZE 20  // Total number of data elements
#define MAX_VAL 100   // Value range 0-99

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *local_bucket = NULL;
    int local_count = 0;

    if (rank == 0) {
        // --- Master Process ---
        printf("Generating %d random numbers with %d processes...\n", DATA_SIZE, size);
        int raw_data[DATA_SIZE];
        srand(time(NULL));
        
        // 1. Generate random numbers
        printf("Original: ");
        for (int i = 0; i < DATA_SIZE; i++) {
            raw_data[i] = rand() % MAX_VAL;
            printf("%d ", raw_data[i]);
        }
        printf("\n\n");

        // 2. Prepare Buckets (Simple implementation: use 2D array for temporary storage)
        // Range interval: Each rank is responsible for a range of (MAX_VAL / size)
        int range = MAX_VAL / size + 1;
        int *buckets[size];
        int counts[size];
        
        for(int i=0; i<size; i++) {
            buckets[i] = (int*)malloc(sizeof(int) * DATA_SIZE); // Allocate sufficient memory
            counts[i] = 0;
        }

        // 3. Distribute data to temporary buckets
        for (int i = 0; i < DATA_SIZE; i++) {
            int target_rank = raw_data[i] / range;
            if (target_rank >= size) target_rank = size - 1;
            buckets[target_rank][counts[target_rank]++] = raw_data[i];
        }

        // 4. Send data to each Slave (including Rank 0 itself)
        for (int i = 0; i < size; i++) {
            if (i == 0) {
                // Send to self
                local_count = counts[i];
                local_bucket = (int*)malloc(sizeof(int) * local_count);
                for(int k=0; k<local_count; k++) local_bucket[k] = buckets[i][k];
            } else {
                // Tell Slave how much data to expect
                MPI_Send(&counts[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                // Send actual data
                MPI_Send(buckets[i], counts[i], MPI_INT, i, 1, MPI_COMM_WORLD);
            }
            free(buckets[i]);
        }

    } else {
        // --- Slave Process ---
        // 1. Receive data count
        MPI_Recv(&local_count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        // 2. Receive data
        local_bucket = (int*)malloc(sizeof(int) * local_count);
        MPI_Recv(local_bucket, local_count, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // --- All processes execute in parallel ---
    
    // 5. Local Sort (Sequential Sort per Bucket)
    qsort(local_bucket, local_count, sizeof(int), compare);
    
    // 6. Send results back to Rank 0
    if (rank != 0) {
        MPI_Send(&local_count, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(local_bucket, local_count, MPI_INT, 0, 3, MPI_COMM_WORLD);
    } else {
        // --- Master collects results ---
        int *sorted_data = (int*)malloc(sizeof(int) * DATA_SIZE);
        int current_idx = 0;

        // Insert Rank 0's own data
        for (int i = 0; i < local_count; i++) {
            sorted_data[current_idx++] = local_bucket[i];
        }

        // Receive data from other Ranks
        for (int i = 1; i < size; i++) {
            int recv_count;
            MPI_Recv(&recv_count, 1, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            int *recv_buf = (int*)malloc(sizeof(int) * recv_count);
            MPI_Recv(recv_buf, recv_count, MPI_INT, i, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            for (int k = 0; k < recv_count; k++) {
                sorted_data[current_idx++] = recv_buf[k];
            }
            free(recv_buf);
        }

        // 7. Display final result
        printf("Sorted:   ");
        for (int i = 0; i < DATA_SIZE; i++) {
            printf("%d ", sorted_data[i]);
        }
        printf("\n");
        free(sorted_data);
    }

    free(local_bucket);
    MPI_Finalize();
    return 0;
}
```

##### Complexity Analysis

**1. Sequential Bucket Sort:**
*   Distribute numbers to buckets: $O(n)$
*   Sequential sort each bucket: $m \times (\frac{n}{m} \log(\frac{n}{m}))$
*   **Overall:**
    $O(n + n \log(\frac{n}{m})) = O(n \log(\frac{n}{m}))$

**2. Parallelize Sorting (One process per bucket):**
*   Distribute numbers to buckets: $O(n)$ (Sequential bottleneck)
*   Sequential sort each bucket (Parallel): $\frac{n}{m} \log(\frac{n}{m})$
*   **Overall:**
    $O(n + \frac{n}{m} \log(\frac{n}{m}))$

**3. Further Parallelized Bucket Sort:**
*   **Goal:** Parallelize the partitioning step to remove the $O(n)$ bottleneck.
*   **Steps:**
    1.  Partition numbers evenly across $m$ processes.
    2.  Each process divides its local numbers into small buckets.
    3.  **All-to-All Exchange:** Processes exchange small buckets to merge them into large global buckets.
    4.  Each process sorts its specific large bucket sequentially.

---

#### 2. Merge Sort
**Concept:** Divide & Conquer approach.

```c
/**
 * MPI Merge Sort
 * Compile: mpicc merge_sort.c -o merge_sort
 * Run:     mpirun -np 4 ./merge_sort
 * Note:    This example assumes DATA_SIZE is divisible by the number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mpi.h>

#define DATA_SIZE 32

// Merge two sorted arrays
int* merge_arrays(int *arr1, int n1, int *arr2, int n2) {
    int *result = (int*)malloc((n1 + n2) * sizeof(int));
    int i = 0, j = 0, k = 0;
    
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) 
            result[k++] = arr1[i++];
        else 
            result[k++] = arr2[j++];
    }
    while (i < n1) result[k++] = arr1[i++];
    while (j < n2) result[k++] = arr2[j++];
    
    return result;
}

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *global_data = NULL;
    int local_n = DATA_SIZE / size; // Number of elements per process
    int *local_data = (int*)malloc(local_n * sizeof(int));

    if (rank == 0) {
        // --- Master: Generate data ---
        global_data = (int*)malloc(DATA_SIZE * sizeof(int));
        srand(time(NULL));
        printf("Original: ");
        for (int i = 0; i < DATA_SIZE; i++) {
            global_data[i] = rand() % 100;
            printf("%d ", global_data[i]);
        }
        printf("\n\n");
    }

    // 1. Scatter: Distribute data evenly to all processes
    MPI_Scatter(global_data, local_n, MPI_INT, 
                local_data, local_n, MPI_INT, 
                0, MPI_COMM_WORLD);

    // 2. Local Sort: Sort local partition first
    qsort(local_data, local_n, sizeof(int), compare);

    // 3. Tree Reduction Merge
    // In each step, half of the processes send data, the other half receive and merge
    int step = 1;
    while (step < size) {
        if (rank % (2 * step) == 0) {
            // --- Receiver (Merge) ---
            int sender = rank + step;
            if (sender < size) {
                int recv_count;
                // Simplified logic: Assuming count after merge is calculable.
                // In practice, if data is uneven, need to send count first.
                // In this perfect binary case, incoming size equals local size.
                int incoming_n = local_n; 

                int *recv_buf = (int*)malloc(incoming_n * sizeof(int));
                
                MPI_Recv(recv_buf, incoming_n, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                
                // Merge incoming data with local data
                int *new_data = merge_arrays(local_data, local_n, recv_buf, incoming_n);
                
                // Update local data pointer and size
                free(local_data);
                free(recv_buf);
                local_data = new_data;
                local_n += incoming_n;
            }
        } else {
            // --- Sender ---
            int receiver = rank - step;
            // Send local data to receiver
            MPI_Send(local_data, local_n, MPI_INT, receiver, 0, MPI_COMM_WORLD);
            // Process finishes task after sending, break loop
            break; 
        }
        step *= 2;
    }

    // 4. Output result
    if (rank == 0) {
        printf("Sorted:   ");
        for (int i = 0; i < local_n; i++) {
            printf("%d ", local_data[i]);
        }
        printf("\n");
        free(global_data);
    }

    free(local_data);
    MPI_Finalize();
    return 0;
}
```

**Complexity:**
*   **Sequential:** $O(n \log n)$

**Parallel Analysis (Tree-based communication):**
In a tree-structured reduction (like the MPI implementation provided earlier), the complexity is dominated by the merging steps as data moves up the tree.

*   **Communication Overhead ($T_{comm}$):**
    Data movement decreases by half at each level.
    $T_{comm} = O(2(\frac{n}{2} + \frac{n}{4} + \dots + 1)) = O(n)$

*   **Computation Time ($T_{comp}$):**
    Merge operations at each level.
    $T_{comp} = O(n + \frac{n}{2} + \frac{n}{4} + \dots + 2) = O(n)$

*   **Conclusion:** In a standard parallel merge sort, the complexity often reduces to $O(n)$ due to the merging and communication overhead, rather than the ideal $O(\log n)$.

#### 3. Quick Sort
**Concept:** Iteratively pick pivot and partition numbers.

```c
/**
 * MPI Quick Sort
 * Compile: mpicc quick_sort.c -o quick_sort
 * Run:     mpirun -np 4 ./quick_sort
 * Note:    This example assumes DATA_SIZE is divisible by the number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

#define DATA_SIZE 32

// Comparison function for qsort
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(int *arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quicksort(arr, low, p - 1);
        quicksort(arr, p + 1, high);
    }
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *global_data = NULL;
    int local_n = DATA_SIZE / size; // Number of elements per process
    int *local_data = (int*)malloc(local_n * sizeof(int));

    if (rank == 0) {
        // --- Master: Generate data ---
        global_data = (int*)malloc(DATA_SIZE * sizeof(int));
        srand(time(NULL));
        printf("Original: ");
        for (int i = 0; i < DATA_SIZE; i++) {
            global_data[i] = rand() % 100;
            printf("%d ", global_data[i]);
        }
        printf("\n\n");
    }

    // 1. Scatter: Distribute data evenly to all processes
    MPI_Scatter(global_data, local_n, MPI_INT, 
                local_data, local_n, MPI_INT, 
                0, MPI_COMM_WORLD);

    int dimensions = (int)log2(size);

    for (int i = 0; i < dimensions; i++) {
        int pivot = 0;
        if (rank == 0) {
            if (local_n > 0) {
                pivot = local_data[0];
            }
            else {
                pivot = 0;
            }
        }
    
        MPI_Bcast(&pivot, 1, MPI_INT, 0, MPI_COMM_WORLD);

        int *small_list = (int*)malloc(local_n * sizeof(int));
        int *large_list = (int*)malloc(local_n * sizeof(int));
        int s_count = 0;
        int l_count = 0;

        for(int k = 0; k < local_n; k++) {
            if (local_data[k] <= pivot) {
                small_list[s_count++] = local_data[k];
            } else {
                large_list[l_count++] = local_data[k];
            }
        }

        int partner = rank ^ (1 << (dimensions - 1 - i));

        int *recv_buf = NULL;
        int recv_count = 0;

        if(rank < partner) {
            MPI_Send(&l_count, 1, MPI_INT, partner, 0, MPI_COMM_WORLD);
            MPI_Send(large_list, l_count, MPI_INT, partner, 1, MPI_COMM_WORLD);

            MPI_Recv(&recv_count, 1, MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            recv_buf = (int*)malloc(recv_count * sizeof(int));
            MPI_Recv(recv_buf, recv_count, MPI_INT, partner, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            free(local_data);
            local_n = s_count + recv_count;
            local_data = (int*)malloc(local_n * sizeof(int));

            memcpy(local_data, small_list, s_count * sizeof(int));
            memcpy(local_data + s_count, recv_buf, recv_count * sizeof(int));
        }
        else {
            MPI_Recv(&recv_count, 1, MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            recv_buf = (int*)malloc(recv_count * sizeof(int));
            MPI_Recv(recv_buf, recv_count, MPI_INT, partner, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            MPI_Send(&s_count, 1, MPI_INT, partner, 0, MPI_COMM_WORLD);
            MPI_Send(small_list, s_count, MPI_INT, partner, 1, MPI_COMM_WORLD);

            free(local_data);
            local_n = l_count + recv_count;
            local_data = (int*)malloc(local_n * sizeof(int));
            
            memcpy(local_data, recv_buf, recv_count * sizeof(int));
            memcpy(local_data + recv_count, large_list, l_count * sizeof(int));
        }

        free(small_list);
        free(large_list);
        if(recv_buf) {
            free(recv_buf);
        }
    }

    quicksort(local_data, 0, local_n - 1);

    int *recv_counts = NULL;
    int *displs = NULL;
    int *final_data = NULL;

    if (rank == 0) {
        recv_counts = (int*)malloc(size * sizeof(int));
    }

    MPI_Gather(&local_n, 1, MPI_INT, recv_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        displs = (int*)malloc(size * sizeof(int));
        final_data = (int*)malloc(DATA_SIZE * sizeof(int));

        displs[0] = 0;
        for (int i = 1; i < size; i++) {
            displs[i] = displs[i - 1] + recv_counts[i - 1];
        }
    }

    MPI_Gatherv(local_data, local_n, MPI_INT, 
                final_data, recv_counts, displs, MPI_INT, 
                0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sorted:   ");
        int total_len = displs[size-1] + recv_counts[size-1];
        for (int i = 0; i < total_len; i++) {
            printf("%d ", final_data[i]);
        }
        printf("\n");
        free(global_data);
        free(recv_counts);
        free(displs);
        free(final_data);
    }

    free(local_data);
    MPI_Finalize();
    return 0;
}
```

**Complexity:**
*   **Sequential:** $O(n \log n)$

*   **Parallel:** $O(n)$

*   **Conclusion:** In a standard parallel quick sort, the complexity often reduces to $O(n)$ due to the merging and communication overhead, rather than the ideal $O(\log n)$.

### B-Body Simulation

## Synchronous Computations
