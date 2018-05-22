// Simple_Linked_List: main.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdio.h>

typedef struct _node
{
	int key;
	struct _node *next;
} NODE;

extern NODE *head, *tail;

extern void list_init();
extern void list_print();
extern int ordered_insert(int k);
extern NODE *node_find(int k);
extern NODE *after_insert(NODE *t, int k);
extern int next_delete(NODE *t);
extern NODE *node_insert(int k, int t);
extern int node_delete(int k);
extern NODE *all_delete();
extern int node_num_get();

int main()
{
	printf("Simple Linked List\n");

	list_init();
	printf("Current node# = %d\n", node_num_get());

	ordered_insert(10);
	ordered_insert(5);
	ordered_insert(8);
	ordered_insert(3);
	ordered_insert(1);
	ordered_insert(7);
	ordered_insert(8);

	list_print();
	printf("Current node# = %d\n", node_num_get());

	NODE *t;
	t = node_find(4);
	printf("Finding 4 is %ssuccessful\n", (t == tail) ? "un" : "");
	t = node_find(5);
	printf("Finding 5 is %ssuccessful\n", (t == tail) ? "un" : "");

	printf("Inserting 9 after 5\n");
	after_insert(t, 9);
	list_print();

	t = node_find(10);
	printf("Deleting next last node\n");
	next_delete(t);
	list_print();
	printf("Current node# = %d\n", node_num_get());

	t = node_find(3);
	printf("Deleting next 3\n");
	next_delete(t);
	list_print();
	printf("Current node# = %d\n", node_num_get());

	printf("Inserting 2 before 3\n");
	node_insert(2, 3);
	list_print();
	printf("Current node# = %d\n", node_num_get());

	printf("Deleting node 2\n");
	if (!node_delete(2))
		printf("Deleting node 2 is unsuccessful\n");
	list_print();
	printf("Current node# = %d\n", node_num_get());

	printf("Deleting node 1\n");
	node_delete(1);
	list_print();
	printf("Current node# = %d\n", node_num_get());

	printf("Deleting all node\n");
	all_delete();
	list_print();
	printf("Current node# = %d\n", node_num_get());

	ordered_insert(9);
	ordered_insert(5);
	ordered_insert(7);
	ordered_insert(3);
	ordered_insert(1);

	list_print();
	printf("Current node# = %d\n", node_num_get());

    return 0;
}

