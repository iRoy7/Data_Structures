#include <stdio.h>
const int IMIN = -2147483648;
const int IMAX = 2147483647;
const int NMAX = 1001;
int trr[NMAX];
int nums = 0;

// Bottom-up
// Heapify: restores heap sequence
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

// Heapify: restores heap sequence
void downheap(int a[], int n, int k)
{
	int i, val;
	val = a[k];

	while (k <= n / 2)
	{
		i = k << 1;
		if (i < n && a[i] < a[i + 1])
		{
			i++;
		}

		if (val >= a[i])
			break;
		
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
		insert(a, &hn, a[i]);
	}
	
	//printf("heap number - %d\n", hn);
	//for (int i = 0; i <= n; i++)
	//	printf("%d ", a[i]);
	//printf("\n");

	// POP
	for (int i = hn; i >= 1; i--)
	{
		a[i] = extract(a, &hn);
		//printf("-----------------------------------------------------\n");
		//for (int j = 1; j <= n; j++)
		//	printf("%d ", a[j]);
		//printf("\n");
	}
}

// SEARCH Algorithm: INIT/INSERT/DELETE/SEARCH
int li_search(int key, int a[], int *num)
{
	int i = 0;
	while (a[i] != key && i < *num)
		i++;
	return (i < *num ? i : (-1));
}
// INSERT
int li_insert(int key, int a[], int *num)
{
	a[(*num)++] = key;
	return *num - 1;
}
// DELETE
int li_delete(int key, int a[], int *num)
{
	if (*num > 0)
	{
		int p;
		if ((p = li_search(key, a, num)) < 0) return -1;
		for (int i = p + 1; i < *num; i++)
		{
			a[i - 1] = a[i];
		}
		(*num)--;
		return p;
	}
	return -1;
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

	int ret = 0;

	// SEARCH '7'
	ret = li_search(7, trr, &nums);
	if (ret < 0)
		printf("7 is not here\n");
	else
		printf("7 is at (%d) index of array\n", ret);

	// INSERT '11'
	if (nums < NMAX)
		ret = li_insert(11, trr, &nums);
	if (ret < 0)
		printf("Insertion: Error!\n");
	else
		printf("11 is saved at (%d) index of array\n", ret);

	// DELETE '5'
	ret = li_delete(5, trr, &nums);
	if (ret < 0)
		printf("5 is not here\n");
	else
		printf("5 is deleted from array\n");

	// Exit
	return 0;
}

