void find_rec(int i, int n, int *A, int q) {
	if (i >= n || A[i] > q)
		return;
	if (A[i] == q) {
		// printf("found\n");
		return;
	}
	find_rec(2 * i + 1, n, A, q);
	find_rec(2 * i + 2, n, A, q);
}

void find(int n, int *A, int q) {
	find_rec(0, n, A, q);
}
