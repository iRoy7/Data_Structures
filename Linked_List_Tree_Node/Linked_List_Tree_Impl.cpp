#include "stdafx.h"
#include <stdio.h>

typedef struct _node
{
	int id;
	int value;
	int sum;
	struct _node *parent;
	struct _node *child;
	struct _node *sibling;
	struct _node *next;
} NODE;

const int MAX_NODE = 10000;
const int MAX_HASH = 100;
NODE Nodes[MAX_NODE];
NODE *Hash[MAX_HASH];
int NodeCnt = 0;

////////////////////////////////////////////////////////
// Function Declaration
NODE *GetNode(int id);
int AddNode(int id, int pid, int value);
int RemoveNode(int id);
int MoveNode(int id, int pid);
int GetValueSum(int pid);
int GetCurNodeCnt();
//======================================================
inline int HASH(int id) { return id % MAX_HASH; }
inline int GetCurNodeCnt() { return NodeCnt; }
inline int GetValueSum(int id) { NODE *n = GetNode(id);	return n->sum; }

NODE *GetNode(int id)
{
	if (NodeCnt == 0) for (int i = 0; i < MAX_HASH; i++) Hash[i] = 0;

	// find 'id' node via HASH
	int h = HASH(id);
	//printf("[MW] Hash value = (%d)\n", h);
	NODE *n = Hash[h];
	// If there is node having same hash value, 
	// find exact Node and return
	while (n)
	{
		if (n->id == id) return n;
		n = n->next;
	}

	// If there is no node then create new one
	//printf("[MW]--> create new node for (%d)\n", id);
	n = &Nodes[NodeCnt++];
	n->id = id;
	n->child = 0;
	// Hashing
	n->next = Hash[h]; // rearrange current pointer value to 1038 node to 138 new node's next
	Hash[h] = n; // point current pointer of Hash[h] to 138 new node.

	return n;
}

void ReflectParent(NODE *node, int value)
{
	while (node)
	{
		node->sum += value;
		node = node->parent;
	}
}

int AddNode(int id, int pid, int value)
{
	if (pid == -1) NodeCnt = 0;

	NODE *n = GetNode(id);
	NODE *pn = (pid != -1) ? GetNode(pid) : 0;
	n->id = id;
	n->value = value;
	n->sum = value;
	n->parent = pn;
	n->sibling = (pn) ? pn->child : 0;

	if (pn)
	{
		pn->child = n;
		// Update upper tree value after adding new node.
		ReflectParent(pn, value);
		return pn->sum;
	}

	return value;
}

void RemoveTree(NODE *n)
{
	NODE *ch = n->child;

	// Recursive call for sibling node tree
	while (ch)
	{
		NODE *current = ch;
		ch = ch->sibling;
		RemoveTree(current);
	}

	// Update hash table
	int hv = HASH(n->id);
	NODE *s = Hash[hv];
	if (s == n) Hash[hv] = s->next;
	else
	{
		while (s->next != n)
			s = s->next;
		s->next = n->next;
	}
}

int RemoveNode(int id)
{
	NODE *n = GetNode(id);

	if (n->parent)
	{
		ReflectParent(n->parent, -(n->sum));

		if (n->parent->child == n)
			n->parent->child = n->sibling;
		else
		{
			NODE *p = n->parent->child;
			while (p->sibling != n) p = p->sibling;
			p->sibling = n->sibling;
		}

#if 0 // Using double pointer
		NODE **np = &n->parent->child;
		while (*np != n) np = &(*np)->sibling;
		*np = (*np)->sibling;
#endif

		RemoveTree(n);
	}
	else NodeCnt = 0;

	return n->sum;
}

int MoveNode(int id, int pid)
{
	NODE *n = GetNode(id);

	// (1) Remove
	if (n->parent->child == n)
		n->parent->child = n->sibling;
	else
	{
		NODE *p = n->parent->child;
		while (p->sibling != n) p = p->sibling;
		p->sibling = n->sibling;
	}

	ReflectParent(n->parent, -(n->sum));

	// (2) Add
	NODE *pn = GetNode(pid);
	n->parent = pn;
	n->sibling = pn->child;
	pn->child = n;

	ReflectParent(pn, n->sum);

	return pn->sum;
}
