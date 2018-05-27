#include <stdio.h>
const int IMAX = 2147483647;
const int IMIN = -2147483648;
const int NMAX = 1001;
int trr[NMAX];
int nums = 0;

// HEAP SORTING
void upheap(int a[], int k)
{// After PUSH, upheap the node
	int v;
	v = a[k];
	a[0] = IMAX;

	while (a[k / 2] <= v)
	{
		a[k] = a[k / 2];
		k /= 2;
	}
	a[k] = v;
}

void downheap(int a[], int n, int k)
{// After POP, downheap the last node which moved to top
	int i, v;
	v = a[k];

	while (k <= n / 2)
	{
		i = k << 1;
		if (i < n && a[i] < a[i + 1]) i++;
		if (v >= a[i]) break;
		a[k] = a[i];
		k = i;
	}
	a[k] = v;
}

void insert(int a[], int *n, int v)
{
	a[++(*n)] = v;
	upheap(a, *n);
}

int extract(int a[], int *n)
{
	int v = a[1];
	a[1] = a[(*n)--];
	downheap(a, *n, 1);
	return v;
}

void heap_sort(int a[], int n)
{
	int hn = 0;
    // PUSH
	for (int i = 1; i <= n; i++)
		insert(a, &hn, a[i]);
    // POP
	for (int i = hn; i >= 1; i--)
		a[i] = extract(a, &hn);
}

// Searching Algorithm - Init/Insert/Delete/Search
int li_search(int key, int a[], int *num)
{
	int i = 0; 
	while (a[i] != key && i < *num) i++;
	return (i < *num ? i : -1);
}
int lfi_search(int key, int a[], int *num)
{
	int p;
	if ((p = li_search(key, a, num)) < 0) return -1;
	for (int i = p - 1; i >= 0; i--) a[i + 1] = a[i];
	a[0] = key;
	return 0;
}
int li_insert(int key, int a[], int *num)
{
	a[(*num)++] = key;
	return *num - 1;
}
int li_delete(int key, int a[], int *num)
{
	if (*num > 0)
	{
		int p;
		if ((p = li_search(key, a, num)) < 0) return -1;
		for (int i = p + 1; i < *num; i++) a[i - 1] = a[i];
		(*num)--;
		return p;
	}
	return -1;
}

int main()
{
	int arr[11] = { IMIN, 4, 5, 2, 6, 7, 8, 3, 1, 10, 9 };
	heap_sort(arr, 10);
	// INIT - Data generation
	for (int i = 1; i <= 10; i++)
	{
		printf("%d ", arr[i]);
		trr[i - 1] = arr[i];
		nums++;
	}
	printf("\n");
	int ret = 0;
    
	// SEARCH
	ret = li_search(7, trr, &nums);
	if (ret < 0)
		printf("7 is not here\n");
	else
		printf("7 is at (%d) index of array\n", ret);
	
    // INSERT
	if (nums < NMAX) ret = li_insert(11, trr, &nums);
	printf("11 is saved at (%d) index of array\n", ret);
	
    // DELETE
	ret = li_delete(5, trr, &nums);
	if (ret < 0)
		printf("5 is not here\n");
	else
		printf("5 is deleted from array\n");

	return 0;
}
