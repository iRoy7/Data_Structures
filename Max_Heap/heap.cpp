#include <stdio.h>
const int IMIN = -2147483648;
const int IMAX = 2147483647;
const int NMAX = 1001;
int trr[NMAX];
int nums = 0;

// Bottom-up
// heapify: restores heap sequence
void upheap(int a[], int key)
{
	int val;
	val = a[key];
	a[0] = IMAX;

	while (a[key / 2] <= val)
	{
		a[key] = a[key / 2];
		key /= 2;
	}

	a[key] = val;
}

// heapify: restores heap sequence
void downheap(int a[], int n, int k)
{
	int i, val;
	val = a[k];

	while (k <= n / 2)
	{
		i = k << 1;
		if (i < n && a[i] < a[i + 1]) i++;
		if (val >= a[i]) break;
		a[k] = a[i];
		k = i;
	}

	a[k] = val;
}

void insert(int a[], int *n, int val)
{
	a[++(*n)] = val;
	upheap(a, *n);
}

int extract(int a[], int *n)
{
	int val = a[1];
	a[1] = a[(*n)--];
	downheap(a, *n, 1);
	return val;
}

void heap_sort(int a[], int n)
{
	int hn = 0;

	// PUSH
	for (int i = 1; i <= n; i++)
	{
		printf("a[%d] = %d\n", i, a[i]);
		insert(a, &hn, a[i]);
	}

	// POP
	for (int i = hn; i >= 1; i--)
		a[i] = extract(a, &hn);

}

int main()
{
	int arr[11] = { IMIN, 4, 5, 2, 6, 7, 8, 3, 1, 10, 9 };
	heap_sort(arr, 10);

	// INIT - data generation
	for (int i = 1; i <= 10; i++)
	{
		printf("%d ", arr[i]);
		trr[i - 1] = arr[i];
		nums++;
	}

	printf("\n");

	return 0;
}
