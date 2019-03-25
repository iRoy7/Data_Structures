#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

const int NMAX = 1001;

extern void init(void);
extern void hash_chain_add_no_dup_key(int key);
extern void hash_chain_add_dup_key_ok(int key);
extern int hash_chain_find(int key);
extern int hash_chain_delete(int key);
extern void hash_chain_print(void);

// Key data
int dcnt;
unsigned int data[NMAX];

int main()
{
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	int T; scanf("%d", &T);

	for (int tc = 1; tc <= T; ++tc)
	{
		dcnt = 0;
		printf("\n(1) Starts initializing...\n");
		init();

		int num_keys;
		scanf("%d", &num_keys);

		printf("\n(2) Start creating hash table...\n");
		// Creates hash table with keys
		for (int i = 1; i <= num_keys; ++i)
		{
			int kval;
			scanf("%d", &kval);
			data[dcnt++] = kval;
			// (1) Not allow duplicated key
			hash_chain_add_no_dup_key(kval);
			// (2) Allows duplicated key
			//hash_chain_add_dup_key_ok(kval);
			hash_chain_print();
		}

		printf("\n(3) Start finding keys...\n");
		// Searches keys via hash table
		for (int i = 0; i < dcnt; ++i)
		{
			hash_chain_find(data[i]);
		}

		printf("\n(4) Start deleting keys...\n");
		// Deletes keys
		for (int i = 0; i < 4; ++i)
		{
			int dkey;
			scanf("%d", &dkey);
			hash_chain_delete(dkey);
			hash_chain_print();
		}
	}

	return 0;
}
