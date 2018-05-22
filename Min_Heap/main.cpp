#include <stdio.h>
#include <stdlib.h>
const int NHEAP = 100000;

typedef int prior_fnc(int d1, int d2);
typedef struct _heap {
	prior_fnc *cmp;
	int num;
	int heapnodes[NHEAP];
} heap;

extern void h_init(heap *ph, prior_fnc pc);
extern void h_insert(heap *ph, int key);
extern int h_delete(heap *ph);
extern int h_delete_v(heap *ph, int key);
extern int h_top_get(heap *ph);
extern void h_traverse(heap *ph);
extern void h_node_clean(heap *ph);
extern int h_num_get(heap *ph);
extern int is_empty(heap *ph);

int data_prior_cmp(int d1, int d2)
{
	return d2 - d1;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);
	
	heap min_heap;

	h_init(&min_heap, data_prior_cmp);

	int T; scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		int cmds; scanf("%d", &cmds);

		while (cmds--)
		{
			int cmd;
			scanf("%d", &cmd);

			if (cmd == 1)
			{// PUSH
				int d; scanf("%d", &d);
				h_insert(&min_heap, d);
			}
			else if (cmd == 2)
			{// POP
				//int d; scanf("%d", &d);
				//h_delete_v(&min_heap, d);
				int d = 0;
				if (!is_empty(&min_heap))
					d = h_delete(&min_heap);
				printf(" >> pop the top (%d)..\n", d);
			}
			else if (cmd == 3)
			{// TOP
				printf("top is %d\n", h_top_get(&min_heap));
				printf("heap num is %d\n", h_num_get(&min_heap));
			}
			else if (cmd == 4)
			{// TRAVERSE
				h_traverse(&min_heap);
				printf("\n");
			}
		}

		h_node_clean(&min_heap);
	}

	return 0;
}