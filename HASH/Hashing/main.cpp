#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
const int NMAX = 1001;

extern void init(void);
extern void hash_chain_add_dup_key_ok(int key);
extern int hash_chain_find(int key);
extern int hash_chain_delete(int key);
extern void hash_chain_print(void);

// Key data
int dcnt;
int data[NMAX];

int main()
{
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	int T; scanf("%d", &T);

	for (int tc = 1; tc <= T; ++tc)
	{
		dcnt = 0;
		init();

		int elm_num;
		scanf("%d", &elm_num);

		printf("\nStart creating hash table...(2)\n");
		// Creates hash table with Key
		for (int i = 1; i <= elm_num; ++i)
		{
			int kval;
			scanf("%d", &kval);
			data[dcnt++] = kval;
			hash_chain_add_dup_key_ok(kval);
			hash_chain_print();
		}

		printf("\nStart searching...(3)\n");
		// Searches key via hash table
		for (int i = 0; i < dcnt; ++i)
		{
			hash_chain_find(data[i]);
		}

		printf("\nStart deleting...(4)\n");
		// Deletes keys
		for (int i = 0; i < 3; ++i)
		{
			int dkey;
			scanf("%d", &dkey);
			hash_chain_delete(dkey);
			hash_chain_print();
		}
	}

	return 0;
}
