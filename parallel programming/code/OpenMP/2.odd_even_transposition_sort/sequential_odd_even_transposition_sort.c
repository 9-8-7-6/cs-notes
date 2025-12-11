
for (int phase = 0; phase < n; phase++) {
    if(phase % 2 == 0) {
        for (int i = 1; i < n; i += 2) {
            if (a[i - 1] > a[i])
                swap(&a[i - 1], &a[i]);
        }
    }
    else {
        for (int i = 1;i < n - 1; i += 2) {
            if(a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
            }
        }
    }
}