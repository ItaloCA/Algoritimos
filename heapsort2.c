void heapsort(float a[], int p, int r) {
    int k, N = r - p + 1;
    float *pq = a + p - 1;
    for (k = N/2; k >= 1; k--) 
        fixDown(pq, k, N);
    while (N > 1) {
        exch(pq[1], pq[N]); 
        fixDown(pq, 1, --N);
    }
}