#include <stdio.h>

extern void list_init(void);
extern void list_print(void);
extern int node_find(int k);
extern int ordered_insert(int k);
extern int before_insert(int val, int k);
extern int after_insert(int k, int val);
extern int node_delete(int k);
extern int next_delete(int k);
extern int all_delete(void);

int main()
{
	printf("Simple Linked List\n");

	list_init();
	int node_cnt = 0;
	node_cnt = ordered_insert(10);
	node_cnt = ordered_insert(5);
	node_cnt = ordered_insert(8);
	node_cnt = ordered_insert(3);
	node_cnt = ordered_insert(1);
	node_cnt = ordered_insert(7);
	node_cnt = ordered_insert(8);

	printf("Initial Linked List is \n");
	list_print();
	printf("Find 8 key ...\n");
	printf("It's located at %d th in linked list\n", node_find(8));
	printf("Before inserting..\n");
	before_insert(9, 8);
	list_print();
	printf("After inserting..\n");
	after_insert(9, 11);
	list_print();
	printf("Node deleting..\n");
	node_delete(10);
	list_print();
	printf("Node deleting..\n");
	node_delete(8);
	list_print();
	printf("Next deleting..\n");
	next_delete(9);
	list_print();
	printf("All deleting..\n");
	all_delete();
	list_print();

	node_cnt = ordered_insert(10);
	node_cnt = ordered_insert(5);
	node_cnt = ordered_insert(8);
	node_cnt = ordered_insert(3);
	node_cnt = ordered_insert(1);
	node_cnt = ordered_insert(7);
	node_cnt = ordered_insert(8);

	list_print();
	printf("Finding 4 is %ssuccessful\n", (node_find(4)) ? "" : "un");
	printf("Finding 5 is %ssuccessful\n", (node_find(5)) ? "" : "un");
	return 0;
}