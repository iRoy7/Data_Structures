#include <stdio.h>
#define null (0)

const int NMAX = 1001;
const int M = 7; // # of bucket

typedef struct _node {
	int key;
	struct _node *next;
} node;

int ncnt;
// Linked-list for chaining
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
// HASH ADT
// Hash function for numeric type of keys
// h(k) = k mod M
unsigned int hash_func1(int key)
{
	int hash_index = key % M;
	if (hash_index < 0)
		hash_index += M;
	return hash_index;
}

unsigned int hash_func(int key)
{
	key += (key << 12);
	key ^= (key >> 22);
	key += (key << 4);
	key ^= (key >> 9);
	key += (key << 10);
	key ^= (key >> 2);
	key += (key << 7);
	key ^= (key >> 12);
	return (key % M);
}

// Hash function for character string type of key
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
	unsigned int hval = hash_func(key);
	
	// Bucket's first slot(node) pointer
	node *ptr_node = hashtbl[hval];
	// previous node
	node *prev_node = null;

	for (; ptr_node; prev_node = ptr_node, ptr_node = ptr_node->next)
	{
		if (ptr_node->key == key)
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

void hash_chain_add_dup_key_ok(int key)
{
	unsigned int hval = hash_func(key);

	// Bucket's first slot(node) pointer
	node *ptr_node = hashtbl[hval];

	// Creates a new node with key
	node *n = node_get(key);
	n->next = ptr_node;
	hashtbl[hval] = n;
}

int hash_chain_find(int key)
{
	unsigned int hval = hash_func(key);

	node *p;

	for (p = hashtbl[hval]; p; p = p->next)
	{
		if (p->key == key)
		{
			printf("Find (%d) successfully\n", key);
			return 1;
		}
	}

	printf("There is no (%d) key here\n", key);
	return 0;
}

int hash_chain_delete(int key)
{
	unsigned int hval = hash_func(key);

	node *p = hashtbl[hval];
	// First slot is the key
	if (p && p->key == key)
	{
		if (p->next)
		{
			printf("Deletes (%d) ...\n", key);
			hashtbl[hval] = p->next;
		}
		else
		{
			printf("Deletes (%d) ...\n", key);
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
				printf("Deletes (%d) ...\n", key);
				prev->next = p->next;
				return 1;
			}
		}
	}

	printf("Can't find (%d) key to delete!\n", key);
	return 0;
}
