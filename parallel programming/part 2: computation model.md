# Computation Model

---

## Embarrassingly Parallel

A computation that can be divided into a number of **completely independent tasks**.

### 1. Image Transformation
    - Shifting x' = x + deltax, y' = y + deltay
    - Scaling x' = Sx * x, y' = Sy * y
    - Rotation x' = x * cos(theta) + y * sin(theta), y' = -x * sin(theta) + y * cos(theta)
---

### 2. Image Region Partitioning

```c
// master process
for(i = 0, row = 0; i < 48; i++, row += 10) {
    send(row, Pi);
}

for(i = 0; i < 480; i++) {
    for(j = 0; j < 640; j++) {
        temp_map[i][j] = 0;
    }
}

for(i = 0; i < (480 * 640); i++) {
    recv(oldrow, oldcol, newrow, newcol, Pany);
    if (!((newrow < 0) || (newrow >= 480) || (newcol < 0) || (newcol >= 640))) {
        temp_map[newrow][newcol] = map[oldrow][oldcol];
    }
}

for(i = 0; i < 480; i++) {
    for(j = 0; j < 640; j++) {
        map[i][j] = temp_map[i][j];
    }
}

// slave process
recv(row, Pmaster);
for(oldrow = row; oldrow < (row + 10); oldrow++) {
    for(oldcol = 0; oldcol < 640; oldcol++) {
        newrow = oldrow + delta_x;
        newcol = oldcol + delta_y;
        send(oldrow, oldcol, newrow, newcol, Pmaster);
    }
}

```
## Divide-and-Conquer Pipelined Computations

## Synchronous Computations
