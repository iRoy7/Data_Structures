#include <stdio.h>

typedef struct _node
{
	int key;
	struct _node *next;
} Node;

Node nodes[100];
int nidx = 0;
Node *head = NULL;
Node *tail = NULL;

void list_print2(Node *h)
{
	Node *p = h->next;
	Node **dp = &p;
	printf("%-8d - address %p\n", p->key, *dp);
	p = p->next;
	printf("%-8d - address %p\n", p->key, *dp);
	p = p->next;
	printf("%-8d - address %p\n", p->key, *dp);
	p = p->next;
	printf("%-8d - address %p\n", p->key, *dp);

	Node *s = h->next;
	Node **ds = &s;
	printf("%-16d - address %p\n", s->key, *ds);

#if 0
	while (p != tail)
	{
		printf("%d  - address %p\n", p->key, *p);
		Node *s = h->next;

		while (s != tail)
		{
			printf("%-8d  - address %p\n", s->key, s);
			s = s->next;
		}

		p = p->next;
	}
#endif
}


void list_print(Node *h)
{
	Node *p = h->next;
	Node **dp = NULL;
	dp = &(p);
	
	while (p != tail)
	{
		printf("%d  - address %p\n", p->key, *dp);

		Node *s = h->next;
		Node **ds = NULL;
		ds = &(s);
		while (s != tail)
		{
			printf("%-8d  - address %p\n", s->key, *ds);
			s = s->next;
			ds = &(s);
		}

		p = p->next;
		dp = &(p);
	}
}

void main()
{
	printf("Pointer testing\n");
	printf(" Size of int %d\n", sizeof(int));
	printf(" Size of struct %d\n", sizeof(Node));
	head = &nodes[nidx++];
	tail = &nodes[nidx++];

	head->next = tail;
	tail->next = tail;

	Node *p = head;
	Node *n = &nodes[nidx++];
	n->key = 1;
	n->next = tail;
	p->next = n;

	n = &nodes[nidx++];
	n->key = 2; 
	n->next = p->next;
	p->next = n;

	n = &nodes[nidx++];
	n->key = 3;
	n->next = p->next;
	p->next = n;

	n = &nodes[nidx++];
	n->key = 4;
	n->next = p->next;
	p->next = n;

	list_print2(head);
}