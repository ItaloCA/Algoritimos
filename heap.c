#include <stdio.h>

int paraent(int i){
	return i/2;
}

int left(int i){
	return 2*i;
}

int right(int i){
	return 2*i+1;
}

void max_heapify(int* A, int i, int m){
	int l = left(i);
	int r = right(i);
	int maior = 0;
	if (l <= m && A[l] > A[i]){
		maior = l;
	}else{
		maior = i;
	}

	if (r <= m && A[r] > A[maior]){
		maior = r;
	}

	if (maior != i){
		int aux  = A[i];
		A[i]     = A[maior];
		A[maior] = aux;

		max_heapify(A,maior,m);
	}
}

void build_max_heap(int* A, int m){
	for (int i = m/2; i >= 1 ; --i){
		max_heapify(A, i, m);
	}
}

void heapsort(int* A, int m){
	printf("%d\n", A[0]);
	build_max_heap(A, m);
	int l = 0;
	for (int i = m; i >= 2; --i){
		l = left(i);
		int aux  = A[i];
		A[i]     = A[l];
		A[l] 	 = aux;
// // 
		m = m-1;
		max_heapify(A, l, m);
	}
}



int heap_maximum(int* A){
	return A[1];
}

int heap_extract_max(int* A, int m){
	if (m < 1){
		// printf("heap underflow.\n");
	}
	int max  = A[1];
	A[1] = A[m];
	m = m-1;
	max_heapify(A, 1, m);
	return max;
}




int main(){
	int A[] = {1, 5, 4, 9, 3, 6, 7, 8, 2};
	heapsort(A, 9);
	for (int i = 0; i < 9; ++i)
	{
		printf("maior valor %d\n", A[i]);
	}

	return 0;
}
