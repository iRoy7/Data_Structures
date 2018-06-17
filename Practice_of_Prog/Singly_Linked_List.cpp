#include <stdio.h>
#include <string.h>
#define nullptr (0)
//#define eprintf(fmt, …) fprintf (stderr, fmt, __VA_ARGS__)

const int NMAX = 1001;
typedef struct _Nameval
{
	char name[12];
	int value;
	struct _Nameval *next;
} Nameval;

int ncnt;
Nameval nodes[NMAX];
Nameval *head;

Nameval *newitem(char *name, int value)
{
	printf("ROY:M:newitem: (%s), (%d)\n", name, value);
	strcpy_s(nodes[ncnt].name, name);
	nodes[ncnt].value = value;
	nodes[ncnt].next = nullptr;
	return &nodes[ncnt++];
	/*/
	Nameval *n = &nodes[ncnt++];
	strcpy_s(n->name, name);
	n->value = value;
	n->next = nullptr;
	return n;
	*/
}

void init(void)
{
	printf("ROY:M:init\n");
	ncnt = 0;
	for (int i = 0; i < NMAX; i++)
		nodes[i].next = nullptr;

	char name[12] = "head";
	head = newitem(name, (-1));
}

Nameval *addfront(Nameval *listp, Nameval *newp)
{
	printf("ROY:M:addfront\n");

	if (!listp) return nullptr;
	newp->next = listp->next;
	listp->next = newp;
	return listp;
}

Nameval *addend(Nameval *listp, Nameval *newp)
{
	printf("ROY:M: addend\n");
	Nameval *p;

	if (listp == nullptr)
		return newp;
	for (p = listp; p->next != nullptr; p = p->next)
		;
	/*
	p = listp;
	while (p) p = p->next;
	*/
	p->next = newp;
	return listp;
}

Nameval *lookup(Nameval *listp, char *name)
{
	for (; listp != nullptr; listp = listp->next)
		if (strcmp(name, listp->name) == 0)
			return listp;
	return nullptr;
}

void printnv(Nameval *p, void *arg)
{
	char *fmt;
	fmt = (char *)arg;
	printf(fmt, p->name, p->value);
}

void apply(Nameval *listp, void (*fn)(Nameval *, void *), void *arg)
{
	printf("ROY:M:>>>>> apply\n");
	if (!listp) return;
	for (; listp->next != nullptr; listp = listp->next)
		(*fn)(listp->next, arg);
}

void inccounter(Nameval *p, void *arg)
{
	int *ip;
	ip = (int *)arg;
	(*ip)++;
}

void freeall(Nameval *listp)
{
	printf("ROY:M: freeall ..\n");
	Nameval *next;

	for (; listp->next != nullptr; listp = next)
	{
		next = listp->next;
		listp->next = nullptr;
	}

	listp = nullptr;
}

Nameval *delitem(Nameval *listp, char *name)
{
	printf("ROY:M: delitem ..\n");
	Nameval *p, *prev;
	prev = nullptr;
	for (p = listp; p != nullptr; p = p->next)
	{
		if (strcmp(name, p->name) == 0)
		{
			if (prev == nullptr)
				listp = p->next;
			else
				prev->next = p->next;
			return listp;
		}
		prev = p;
	}

	printf("delitem: %s not in list", name);
	return nullptr;
}

int main(void)
{
	init();

	char name[12] = "ROY";
	int val = 8919;
	Nameval *n = newitem(name, val);
	head = addfront(head, n);

	char name2[12] = "MJ";
	val = 6205;
	Nameval *n2 = newitem(name2, val);
	head = addfront(head, n2);

	Nameval *p = head;
	while (p->next)
	{
		printf("%s: %d\n", p->next->name, p->next->value);
		p = p->next;
	}

	char name3[12] = "MWJ";
	val = 911;
	Nameval *n3 = newitem(name3, val);
	head = addend(head, n3);

	char fmt[8] = "%s: %x\n";
	apply(head, printnv, fmt);

	char name4[12] = "foolish";
	val = 102948;
	Nameval *n4 = newitem(name4, val);
	head = addend(head, n4);

	apply(head, printnv, fmt);

	delitem(head, name4);
	apply(head, printnv, fmt);

	freeall(head);

	apply(head, printnv, fmt);

	return 0;
}
