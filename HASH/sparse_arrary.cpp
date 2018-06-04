//https://www.hackerrank.com/challenges/sparse-arrays/problem
#include <stdio.h>

const int NMAX = 1001;
const int HMAX = 3119;
const int null = 0;

typedef struct _node
{
	char key[20];
	struct _node *next;
} node;

unsigned int my_pow(unsigned int base, int exp)
{
	unsigned int res = 1;
	while (exp)
	{
		if (exp & 1)
			res *= base;
		exp >>= 1;
		base *= base;
	}
	return res;
}


node nodes[NMAX];
int ncnt;
// HASH
node *hashtbl[HMAX];
unsigned long long hashfunc(const char *str)
{
	unsigned long long hash = 5381;
	int c;

	while (c = *str++)
		hash = (((hash << 5) + hash) + c) % HMAX;

	return hash % HMAX;
}

unsigned long long hashfunc2(const char *name)
{
	unsigned long long tmp[7];
	for (int i = 0; i < 7; i++)
		tmp[i] = 0;

	int idx= 0;
	for (int i = 0; name[i]; i++)
		tmp[idx++] = name[i] - 'a';

	unsigned long long ret = 0;
	for (int i = 0; i < 6; i++)
	{
		ret += tmp[i] * my_pow(26, i);
	}

	//printf("D: %s - %lld\n", name, ret);
	return ret % HMAX;
}

void init(void)
{
	ncnt = 0;
	for (int i = 0; i < HMAX; i++)
		hashtbl[i] = null;
}

void my_strcpy(char *src, char *dest)
{
	while (*src != '\0') {
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
}

int my_strcmp(char *str1, char *str2)
{
	int i = 0;
	while (str1[i] != '\0') {
		if (str1[i] != str2[i]) break;
		i++;
	}
	return (str1[i] - str2[i]);
}

int main()
{
	//printf("Programming start..\n");
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	int T; scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		// Clean Hash
		init();

		int SN= 0;  scanf("%d", &SN);
		for (int i = 0; i < SN; i++)
		{
			char str[20];
			//gets_s(str);
			scanf(" %[^\n]\n", str);
			//printf("R: input string %s\n", str);
			// Hashing..
			unsigned long long hv = hashfunc(str);
			//printf("R: hash value(%lld) for %s\n", hv, str);

			//hashtbl[hv]++;
			node *n = null;
			n = hashtbl[hv];
			n = &nodes[ncnt++];
			my_strcpy(str, n->key);
			n->next = hashtbl[hv];
			hashtbl[hv] = n;
		}

		int QN= 0; scanf("%d", &QN);
		for (int i = 0; i < QN; i++)
		{
			char qstr[20];
			//gets_s(qstr);
			scanf(" %[^\n]\n", qstr);
			//printf("R: query string %s\n", qstr);
			// Hash query..
			unsigned long long hv = hashfunc(qstr);
			//printf("R: hash value(%lld) for %s\n", hv, qstr);

			int count = 0;
			node *p = hashtbl[hv];
			//printf("D: find key %s\n", p->key);
			while (p)
			{
				if (!my_strcmp(p->key, qstr)) count++;
				p = p->next;
			}
			//printf("%d\n", hashtbl[hv]);
			printf("%d\n", count);
		}
	}

	return 0;
}
