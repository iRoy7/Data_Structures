#include <stdio.h>
const int NMAX = 6;
const int XRANGE = 10001;

// INSERTION
// Inserts the least number into proper position on left side
// From index 1(2nd cell)
void insertion_sort(int arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int key = arr[i];
		int j;
		for (j = i - 1; j >= 0 && arr[j] > key; --j)
			arr[j + 1] = arr[j];
		arr[j + 1] = key;
	}
}

// BUBBLE
// Bubble the largest number toward the right
// Quadratic time: O(N*N)
// Comparison: (N-1) + (N-2) + (N-3) ... + 1 
// SWAP : (N-1) + (N-2) + (N-3) ... + 1 
void bubble_sort(int arr[], int n)
{
	for (int i = n - 1; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

// SELECTION
// Selects the least number and puts it on left side of selection
void selection_sort(int arr[], int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		int minkey = i;

		for (int j = i + 1; j < n; ++j)
		{// Finds an index of the least number
			if (arr[j] < arr[minkey])
				minkey = j;
		}
		// Puts it on left side of selection
		int tmp = arr[i];
		arr[i] = arr[minkey];
		arr[minkey] = tmp;
	}
}

// QUICK
// Divide and Conquer
static int A[NMAX + 1] = { 103, 5 , 10, 35, 59, 6205, 8919 };
void qsort(int s, int e)
{
	if (s >= e) return;
	int l, r, p, tmp;
	l = s - 1, r = e + 1, p = A[(s + e) / 2];
	while (1)
	{
		while (A[++l] < p);
		while (A[--r] > p);
		if (l >= r) break;
		tmp = A[l], A[l] = A[r], A[r] = tmp;
	}
	qsort(s, l - 1);
	qsort(r + 1, e);
}

// COUNTING
int count[XRANGE];
void count_sort(int arr[], int n, int max)
{
	for (int i = 0; i < n; ++i) count[arr[i]]++;
	int idx = 0; 
	for (int i = 0; i < max; ++i)
		if (count[i] != 0)
			for (int j = 0; j < count[i]; ++j)
				arr[idx++] = i;
}

const int SMAX = 101;
const int stack_limit = 100;
int rstk_top = -1;	// top of right stack
int lstk_top = -1;	// top of left stack
int RSTK[SMAX];		// Right sorted stack
int LSTK[SMAX];		// Left unsorted stack

void stack_sort()
{
	// POP left stack
	while (lstk_top != (-1))
	{
		int x = LSTK[lstk_top--];
		printf(" Pop (%d) in Left unsorted stack\n", x);

		while (rstk_top != (-1) && RSTK[rstk_top] > x)
		{
			printf(" Right stack's top value is greater than current popped x in unsorted left stack.\n");
			printf(" %d: (R) -> (L)\n", RSTK[rstk_top]);
			LSTK[++lstk_top] = RSTK[rstk_top--];
		}

		// PUSH right stack
		printf(" PUSHes x into sorted stack\n");
		RSTK[++rstk_top] = x;
	}

	printf(" Stores sorted items into Left stack.\n");
	while (rstk_top != (-1))
		LSTK[++lstk_top] = RSTK[rstk_top--];
}

void print_arr(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
	printf("\n\n");
}

int main(void)
{
	qsort(0, NMAX);
	print_arr(A, NMAX + 1);

	int arr0[NMAX] = { 10, 3, 9, 2, 5, 1 };
	insertion_sort(arr0, NMAX);
	print_arr(arr0, NMAX);

	int arr1[NMAX] = { 3, 10, 9, 2, 5, 1 };
	bubble_sort(arr1, NMAX);
	print_arr(arr1, NMAX);

	int arr2[NMAX] = { 3, 5, 10, 35, 13, 9 };
	int arr3[NMAX] = { 3, 10, 9, 2, 5, 1 };
	selection_sort(arr2, NMAX);
	print_arr(arr2, NMAX);
	selection_sort(arr3, NMAX);
	print_arr(arr3, NMAX);

	int arr4[NMAX + 1] = { 103, 5 , 10, 35, 59, 6205, 8919 };
	count_sort(arr4, NMAX + 1, 9000);
	print_arr(arr4, NMAX + 1);

	// Sorted right stack
	RSTK[++rstk_top] = 1;
	RSTK[++rstk_top] = 3;
	RSTK[++rstk_top] = 8;
	RSTK[++rstk_top] = 12;

	// Unsorted left stack;
	LSTK[++lstk_top] = 7;
	LSTK[++lstk_top] = 10;
	LSTK[++lstk_top] = 5;

	stack_sort();

	print_arr(LSTK, 7);

	return 0;
}
