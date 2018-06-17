#include <stdio.h>
#include <string.h>
#define nullptr (0)
const int NMAX = 1001;
const int HMAX = 3119;
typedef struct _Nameval
{
	char name[12];
	int value;
	struct _Nameval *next;
} Nameval;

enum { MULTIPLIER = 31 };
int ncnt;
Nameval nodes[NMAX];
Nameval *hashtbl[HMAX];
unsigned int hashfunc(char *str)
{
	unsigned int hv;
	unsigned char *p;

	hv = 5381;
	for (p = (unsigned char *)str; *p != '\0'; p++)
		hv = MULTIPLIER * hv + *p;
	return hv % HMAX;
}
unsigned int hashfunc2(char *str)
{
	unsigned int hv = 5381;
	int c;
	while (c = *str++)
	{
		hv = (((hv << 5) + hv) + c) % HMAX;
	}
	return hv % HMAX;
}

Nameval *lookup(char *name, int create, int value)
{
	int hv;
	Nameval *sym = nullptr;

	hv = hashfunc(name);
	for (sym = hashtbl[hv]; sym != nullptr; sym = sym->next)
		if (strcmp(name, sym->name) == 0)
			return sym;

	if (create)
	{
		printf("R:D: Creating..\n");
		sym = &nodes[ncnt++];
		strcpy_s(sym->name, name);
		sym->value = value;
		sym->next = hashtbl[hv];
		hashtbl[hv] = sym;
	}

	return sym;
}

int main(void)
{
	char name[12] = "ROY";
	int val = 8919;

	lookup(name, 1, val);

	char name2[12] = "MJ";
	val = 6502;

	lookup(name2, 1, val);

	char name3[12] = "MWJ";
	val = 911;

	lookup(name3, 1, val);

	Nameval *p = lookup(name, 1, val);
	printf("%s: %x \n", p->name, p->value);

	return 0;
}
