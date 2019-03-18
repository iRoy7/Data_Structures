#include <stdio.h>

#define null (0)

const int NMAX = 1001;
const int M = 7;

typedef struct _node {
	int key;
	struct _node *next;
} node;

int ncnt;
// Linked List for Chaining
node nodes[NMAX];
// HASH TABLE
node *hashtbl[M];

void init(void)
{
	ncnt = 0;

	for (int i = 0; i < NMAX; ++i)
	{
		nodes[i].key = 0, nodes[i].next = null;
	}
	for (int i = 0; i < M; ++i)
	{
		hashtbl[i] = null;
	}
	printf("Init Success...(1)\n");
}

/////////////////////////////////////////////////////////////////////////
// LINKED LIST
node *node_get(int key)
{
	nodes[ncnt].key = key;
	nodes[ncnt].next = null;
	return &nodes[ncnt++];
}

/////////////////////////////////////////////////////////////////////////
// HASH 
// Numeric Key
// h(k) = k mod M
int hash_func(int key)
{
	int hash_index = key % M;
	if (hash_index < 0)
		hash_index += M;
	return hash_index;
}

// Character String Key
unsigned long long hash_func2(const char *str)
{
	unsigned long long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % M;
	}

	return hash % M;
}

void hash_chain_print(void)
{
	node *p;
	printf("\n=======================================================\n");
	for (int i = 0; i < M; ++i)
	{
		printf("[%d]->", i);
		for (p = hashtbl[i]; p; p = p->next)
		{
			printf("%d->", p->key);
		}
		printf("\n");
	}
	printf("\n=======================================================\n");
}

/////////////////////////////////////////////////////////////////////////
// HASH ADT
void hash_chain_add_no_dup_key(int key)
{
	int hval = hash_func(key);
	
	// Bucket's first slot(node)
	node *bnode = hashtbl[hval];
	// previous node
	node *prev_node = null;
	for (; bnode; prev_node = bnode, bnode = bnode->next)
	{
		if (bnode->key == key)
		{
			//fprintf(stderr, "The key already exsits\n");
			printf("The key already exsits\n");
			return;
		}
	}

	// Create a new node with key
	node *n = node_get(key);
	if (prev_node)
		prev_node->next = n;
	else
		hashtbl[hval] = n;
}

int hash_chain_find(int key)
{
	int hval = hash_func(key);

	node *p;

	for (p = hashtbl[hval]; p; p = p->next)
	{
		if (p->key == key)
		{
			printf("Find %d successfully\n", key);
			return 1;
		}
	}

	printf("There is no %d key here\n", key);
	return 0;
}

int hash_chain_delete(int key)
{
	int hval = hash_func(key);

	node *p = hashtbl[hval];
	// First slot is the key
	if (p->key == key)
	{
		if (p && p->next)
		{
			printf("Deletes %d ...\n", key);
			hashtbl[hval] = p->next;
		}
		else
		{
			printf("Deletes %d ...\n", key);
			hashtbl[hval] = null;
		}

		return 1;
	}

	node *prev = null;
	for (; p; prev = p, p = p->next)
	{
		if (p->key == key)
		{
			if (prev != null)
			{
				printf("Deletes %d ...\n", key);
				prev->next = p->next;
				return 1;
			}
		}
	}

	printf("Can't find %d key to delete!\n", key);
	return 0;
}
