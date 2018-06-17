#include <stdio.h>
#include <string.h>
#include "eprintf.h"
#define nullptr (0)
const int NMAX = 10001;
typedef struct _Nameval
{
	char name[12];
	int value;
	struct _Nameval *left;
	struct _Nameval *right;
} Nameval;

int ncnt;
Nameval nodes[NMAX];
Nameval *rt; // Root

Nameval *newitem(char *name, int value)
{
	strcpy_s(nodes[ncnt].name, name);
	nodes[ncnt].value = value;
	nodes[ncnt].left = nullptr;
	nodes[ncnt].right = nullptr;
	return &nodes[ncnt++];
}

void init(void)
{
	ncnt = 0;
	char name[12] = "2root";
	rt = newitem(name, (-1));
}

Nameval *insert(Nameval *treep, Nameval *newp)
{
	int cmp;

	if (treep == nullptr)
		return newp;
	cmp = strcmp(newp->name, treep->name);
	if (cmp == 0)
	{
		char msg[36] = "insert: duplicate entry %s ignored";
		weprintf(msg, newp->name);
	}
	else if (cmp < 0)
		treep->left = insert(treep->left, newp);
	else
		treep->right = insert(treep->right, newp);

	return treep;
}

Nameval *lookup(Nameval *treep, char *name)
{
	int cmp;

	if (treep == nullptr)
		return nullptr;
	cmp = strcmp(name, treep->name);
	if (cmp == 0)
		return treep;
	else if (cmp < 0)
		return lookup(treep->left, name);
	else
		return lookup(treep->right, name);
}


Nameval *nrlookup(Nameval *treep, char *name)
{
	int cmp;

	while (treep != nullptr)
	{
		cmp = strcmp(name, treep->name);
		if (cmp == 0)
			return treep;
		else if (cmp < 0)
			treep = treep->left;
		else
			treep = treep->right;
	}

	return nullptr;
}

void printnv(Nameval *p, void *arg)
{
	char *fmt;
	fmt = (char *)arg;
	printf(fmt, p->name, p->value);
}

void applyinOrder(Nameval *treep,
	void(*fn)(Nameval *, void *), void *arg)
{//LvR
	if (treep == nullptr) return;
	applyinOrder(treep->left, fn, arg);
	(*fn)(treep, arg);
	applyinOrder(treep->right, fn, arg);
}

void applypostOrder(Nameval *treep,
	void(*fn)(Nameval *, void *), void *arg)
{//LRv
	if (treep == nullptr) return;
	applypostOrder(treep->left, fn, arg);
	applypostOrder(treep->right, fn, arg);
	(*fn)(treep, arg);
}

int main(void)
{
	init();

	char name[12] = "1ROY";
	int val = 8919;
	Nameval *n = newitem(name, val);
	rt = insert(rt, n);

	char name2[12] = "3MJ";
	val = 6205;
	Nameval *n2 = newitem(name2, val);
	rt = insert(rt, n2);

	char name3[12] = "0MWJ";
	val = 911;
	Nameval *n3 = newitem(name3, val);
	rt = insert(rt, n3);

	char fmt[8] = "%s: %x\n";
	applyinOrder(rt, printnv, fmt);

	return 0;
}
