#include "stdafx.h"
#include <stdio.h>

const int MAX_NODE = 10000;
 
typedef struct _node
{
	int key;
	struct _node *next;
} NODE;

NODE nodes[MAX_NODE];
NODE *head, *tail;
int node_idx;
int node_num;

// Function Definitions
void list_init();
void list_print();
int ordered_insert(int k);
NODE *node_find(int k);
NODE *after_insert(NODE *t, int k);
int next_delete(NODE *t);
NODE *node_insert(int k, int t);
int node_delete(int k);
NODE *all_delete();
int node_num_get();

// Function Implementation
void list_init()
{
	for (int i = 0; i < MAX_NODE; i++)
		nodes[i].key = (-1);

	node_idx = 0;
	node_num = 0;
	head = &nodes[node_idx++];
	tail = &nodes[node_idx++];
	head->next = tail;
	tail->next = tail;
}

int node_num_get()
{
	return node_num;
}

void list_print()
{
	if (head->next == tail) return;
	NODE *t = head->next;

	while (t != tail)
	{
		printf("%-8d", t->key);
		t = t->next;
	}
	printf("\n");
}

/* Sorting is important  !*/
int ordered_insert(int k)
{
	NODE *s;
	NODE *p;
	NODE *n;

	p = head;
	s = p->next;

	while (s->key <= k && s != tail)
	{
		p = p->next;
		s = p->next;
	}
	
	n = &nodes[node_idx++], node_num++;
	if (n->key == (-1)) printf("Not used (%d)\n", n->key);
	else printf("Used. Warnning!!!\n");
	n->key = k;
	p->next = n;
	n->next = s;

	return node_num;
}

NODE *node_find(int k)
{
	NODE *s;
	s = head->next;

	while (s->key != k && s != tail)
		s = s->next;
	return s;
}

NODE *after_insert(NODE *t, int k)
{
	NODE *n;
	n = &nodes[node_idx++], node_num++;
	n->key = k;
	n->next = t->next;
	t->next = n;

	return n;
}

int next_delete(NODE *t)
{
	if (t->next == tail) return 0;

	NODE *s;
	s = t->next;
	t->next = t->next->next;

	s->key = (-1);
	s->next = NULL;
	node_num--;

	return 1;
}

NODE *node_insert(int k, int t)
{
	NODE *s;
	NODE *p;
	NODE *n;

	p = head;
	s = p->next;

	while (s->key != t && s != tail)
	{
		p = p->next;
		s = p->next;
	}

	if (s != tail)
	{
		n = &nodes[node_idx]; node_num++;
		n->key = k;
		p->next = n;
		n->next = s;
	}

	return p->next;
}

int node_delete(int k)
{
	NODE *s;
	NODE *p;

	p = head;
	s = p->next;

	while (s->key != k && s != tail)
	{
		p = p->next;
		s = p->next;
	}

	if (s != tail)
	{
		p->next = s->next;
		s->key = (-1);
		s->next = NULL;
		node_num--;

		return 1;
	}

	return 0;
}

NODE *all_delete()
{
	NODE *s;
	NODE *t;
	t = head->next;

	while (t != tail)
	{
		s = t;
		t = t->next;
		s->key = (-1);
		s->next = NULL;
		node_num--;
	}

	head->next = tail;

	return head;
}
