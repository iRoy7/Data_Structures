#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int key;
	struct _node *next;
} node;

node *head;
void node_insert(int k)
{
	node *n = NULL;
	n = (node *)malloc(sizeof(node));
	if (!n) return;
	n->key = 1;
	head = n;

	for (int i = 2; i <= k; i++)
	{
		n->next = (node *)malloc(sizeof(node));
		if (!n->next) return;
		n = n->next;
		n->key = i;
	}

	n->next = head;
}

void after_delete(node *t)
{
	node *p = NULL;
	p = t->next;
	t->next = t->next->next;
	free(p);
}

void josephus(int n, int m)
{
	node_insert(n);

	node *p = NULL;
	p = head;
	printf("\n Answer : ");
	while (p != p->next)
	{
		for (int i = 0; i < m - 1; i++)
			p = p->next;
		printf("%d ", p->next->key);
		after_delete(p);
	}

	printf("%d", p->key);
}

int main()
{
	printf("\n If you want to quit, enter 0 or minus number");

	while (1)
	{
		printf("\nEnter N and M -> ");
		int n, m;
		scanf("%d %d", &n, &m);
		if (n <= 0 || m <= 0)
			return 0;
		josephus(n, m);
	}
}