#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node
{
	int key;
	struct _node *left;
	struct _node *right;
} node;

//STACK ////////////////////////////////////////////////////////////////////
const int SMAX = 100;
node *stack[SMAX];
int top;
void stack_init(void) { top = -1; }
int is_stack_empty(void) {	return (top == (-1)); }
node *push(node *t)
{
	if (top >= SMAX - 1)
	{
		printf("\n  Stack overflow.");
		return NULL;
	}
	stack[++top] = t;
	return t;
}
node *pop(void)
{
	if (top < 0)
	{
		printf("\n  Stack underflow.");
		return NULL;
	}
	return stack[top--];
}

//QUEUE ////////////////////////////////////////////////////////////////////
const int QMAX = 200;
node *queue[QMAX];
int front, rear;
void queue_init(void) { front = rear = 0; }
int is_queue_empty(void) { return front == rear; }
node *put(node *k)
{
	if ((rear + 1) % QMAX == front)
	{
		printf("\n  Queue overflow.");
		return NULL;
	}
	queue[rear] = k;
	rear = ++rear % QMAX;
	return k;
}
node *get(void)
{
	node *i;
	if (front == rear)
	{
		printf("\n  Queue underflow.");
		return NULL;
	}
	i = queue[front];
	front = ++front%QMAX;
	return i;
}

//TREE /////////////////////////////////////////////////////////////////////
node *head, *tail;
void tree_init(void)
{
	head = (node *)malloc(sizeof(node));
	tail = (node *)malloc(sizeof(node));
	head->left = tail;
	head->right = tail;
	tail->left = tail;
	tail->right = tail;
}
int is_operator(int k)
{
	return (k == '+' || k == '-' || k == '*' || k == '/');
}
node *parse_tree_make(char *p)
{
	node *t;
	while (*p)
	{
		while (*p == ' ')
			p++;
		t = (node *)malloc(sizeof(node));
		t->key = *p;
		t->left = tail;
		t->right = tail;
		if (is_operator(*p))
		{
			t->right = pop();
			t->left = pop();
		}
		push(t);
		p++;
	}
	return pop();
}
int is_legal(char *s)
{
	int f = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (is_operator(*s))
			f--;
		else
			f++;
		if (f < 1) break;
		s++;
	}
	return (f == 1);
}

// TREE TRAVERSE ///////////////////////////////////////////////////////////
void visit(node *t)
{
	printf("%c ", t->key);
}
void preorder_traverse(node *t)
{//vLR
	if (t != tail)
	{
		visit(t);
		preorder_traverse(t->left);
		preorder_traverse(t->right);
	}
}
void inorder_traverse(node *t)
{//LvR
	if (t != tail)
	{
		inorder_traverse(t->left);
		visit(t);
		inorder_traverse(t->right);
	}
}
void postorder_traverse(node *t)
{//LRv
	if (t != tail)
	{
		postorder_traverse(t->left);
		postorder_traverse(t->right);
		visit(t);
	}
}
void levelorder_traverse(node *t)
{//Level
	put(t);
	while (!is_queue_empty())
	{
		t = get();
		visit(t);
		if (t->left != tail)
			put(t->left);
		if (t->right != tail)
			put(t->right);
	}
}
inline int max(int a, int b) { return (a > b) ? a : b; }
int tree_height_get(node *t)
{// Tree height
	if (t == NULL) return -1;

	return max(
		tree_height_get(t->left) + 1,
		tree_height_get(t->right) + 1
		);
}

void main(void)
{
	char post[256];
	stack_init();
	queue_init();
	tree_init();
	
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	while (1)
	{
		printf("\n\n Input Postfix expresson -> ");
		gets_s(post);
		//scanf(" %[^\n]\n", post);

		if (*post == NULL)
		{
			printf("\n Input is empty..So Program ends ...\n");
			exit(0);
		}
		if (!is_legal(post))
		{
			printf("\n Expression is not legal.");
			continue;
		}

		head->right = parse_tree_make(post);

		//printf("\n Tree height -> (%d)", tree_height_get(head->right));

		printf("\n Preporder traverse -> ");
		preorder_traverse(head->right);

		printf("\n Inorder traverse -> ");
		inorder_traverse(head->right);

		printf("\n Postorder traverse -> ");
		postorder_traverse(head->right);

		printf("\n Levelorder traverse -> ");
		levelorder_traverse(head->right);
	}
}