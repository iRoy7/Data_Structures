#include <stdio.h>
const int NMAX = 1000;

typedef struct _node
{
	int key;
	struct _node *next;
} node;

node nodes[NMAX];
node *head, *tail;
int nidx = 0;	// node index
int nn = 0;		// node number

void list_init(void)
{
	nidx = nn = 0;
	head = &nodes[nidx++];
	tail = &nodes[nidx++];
	head->next = tail;
	tail->next = tail;
}

void list_print(void)
{
	if (!head) return;
	node *t = head->next;
	while (t != tail && nn > 0)
	{
		printf("%-8d", t->key);
		t = t->next;
	}
	printf("\n number of node is %d\n", nn);
}

int node_find(int k)
{
	if (!head) return 0;
	int ret = 0;
	node *s;
	s = head->next;
	while (s->key != k && s != tail)
		s = s->next, ret++;

	return (s == tail) ? 0 : ret+1;
}

int ordered_insert(int k)
{
	if (!head) return 0;
	node *p;
	node *s;
	p = head;
	s = p->next;

	while (s->key <= k && s != tail)
	{
		p = p->next;
		s = p->next;
	}

	node *n;
	n = &nodes[nidx++], nn++;
	n->key = k;
	p->next = n;
	n->next = s;

	return nn;
}

int before_insert(int val, int k)
{
	if (!head) return 0;

	node *p;
	node *s;
	p = head;
	s = p->next;

	while (s->key != k && s != tail)
	{
		p = p->next;
		s = p->next;
	}
	
	if (s != tail)
	{
		node *n;
		n = &nodes[nidx++], nn++;
		n->key = val;
		p->next = n;
		n->next = s;

		return 1;
	}
	else
	{
		printf("There is no target key!\n");
		return 0;
	}
}

int after_insert(int k, int val)
{
	if (!head) return 0;
	node *s;
	s = head->next;

	while (s->key != k && s != tail)
		s = s->next;

	if (s != tail)
	{
		node *n;
		n = &nodes[nidx++], nn++;
		n->key = val;
		n->next = s->next;
		s->next = n;

		return 1;
	}
	else
	{
		printf("There is no target key!\n");
		return 0;
	}
}

int node_delete(int k)
{
	if (!head) return 0;

	node *p;
	node *s;
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
		s->key = (-1); // DELETE(MAKE it UNUSED)
		s->next = NULL;
		nn--;

		return 1;
	}
	else
	{
		printf("There is no target key!\n");
		return 0;
	}
}

int next_delete(int k)
{
	if (!head) return 0;

	node *s;
	s = head->next;

	while (s->key != k && s != tail)
		s = s->next;

	if (s->next == tail) return 0;

	node *t;
	t = s->next;
	s->next = s->next->next;
	t->key = (-1); // DELETE(MAKE it UNUSED)
	t->next = NULL;
	nn--;

	return 1;
}

int all_delete(void)
{
	if (!head) return 0;

	node *s;
	node *t;

	s = head->next;

	while (s != tail)
	{
		t = s;
		s = s->next;
		t->key = (-1);
		t->next = NULL;
	}

	list_init();

	return 1;
}