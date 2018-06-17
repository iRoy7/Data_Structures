#include <stdio.h>
#define NELEMS(array) (sizeof(array) / sizeof(array[0]))

/* strcmp: s1 < s2 -> (-) returns, */
/* s1 > s2 ->(+) returns, s1 = s2 -> (0) returns */
int mstrcmp(const char *str1, const char *str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0') return (0);
		str1++;
		str2++;
	}
	if (*str1 > *str2) return (1);
	return (-1);
}

/* lookup: Sequence search word which in array. */
int lookup(const char *word, const char *array[])
{
	int i;
	for (i = 0; array[i] != NULL; i++)
		if (mstrcmp(word, array[i]) == 0)
			return i;
	return (-1);
}

typedef struct Nameval Nameval;
struct Nameval {
	const char *name;
	int  value;
};

int lookup2(const char *name, Nameval tab[], int ntab)
{
	int low, high, mid, cmp;

	low = 0; 
	high = ntab - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		cmp = mstrcmp(name, tab[mid].name);
		if (cmp < 0)
			high = mid - 1;
		else if (cmp > 0)
			low = mid + 1;
		else
			return mid;
	}

	return (-1);
}

int main()
{
	const char *word1 = "really";
	const char *word2 = "actually";
	const char *word3 = "quite";
	const char *word4 = "jsut";

	const char *flab[] = {
		"actually",
		"just",
		"quite",
		"really",
		NULL
	};

	int ith = 0;
	ith = lookup(word1, flab);
	printf("%d\n", ith);
	ith = lookup(word2, flab);
	printf("%d\n", ith);
	ith = lookup(word3, flab);
	printf("%d\n", ith);
	ith = lookup(word4, flab);
	printf("%d\n", ith);
	

	Nameval htmlchars[] = {
		"AElig",	0x00c6,
		"Aacute",	0x00c1,
		"Acirc",	0x00c2,
		/*...*/
		"zeta",		0x03b6,
		"smiley",   0x263A,
	};

	printf("The HTML table has %d words\n", NELEMS(htmlchars));
	int half = lookup2("frac12", htmlchars, NELEMS(htmlchars));
	printf("%d\n", half);
	half = lookup2("zeta", htmlchars, NELEMS(htmlchars));
	printf("%d\n", half);

	return 0;
}
