#include <stdio.h>
#include <stdlib.h>
typedef struct _dnode
{ 
  int key;
  struct _dnode *prev;
  struct _dnode *next;
} dnode;

dnode *head = NULL;
dnode *tail = NULL;

void dlist_init()
{
  head = (dnode *)malloc(sizeof(dnode));
  tail = (dnode *)malloc(sizeof(dnode));
  if (head == NULL || tail == NULL) return;
  head->next = tail; head->prev = head;
  tail->next = tail; tail->prev = head;
}

void dlist_print(dnode *p) 
{
  printf("\n");
  while (p != tail)
  {
    printf("%-8d", p->key);
    p = p->next;
  }
  printf("\n");
}

dnode *dnode_find(int k)
{
  dnode *s;
  s = head->next;
  while (s->key != k && s != tail)
    s = s->next;
  return s;
}

dnode *dnode_ptr_insert(int k, dnode *t)
{
  if (t == head) return NULL;
  dnode *n = NULL; 
  n = (dnode *)malloc(sizeof(dnode)); 
  if (n) 
  {
    n->key = k; t->prev->next = n; n->prev = t->prev; t->prev = n; n->next = t;
  }
  else
    printf("Memory allocation had been failed!\n");
  
  return n;
}

int dnode_ptr_delete(dnode *p)
{
  if (p == head || p == tail)  return 0;
  p->prev->next = p->next;
  p->next->prev = p->prev;
  free(p);
  return 1;
}

dnode *dnode_insert(int k, int t)
{
  dnode *n = NULL;
  dnode *s; s = dnode_find(t);
  if (s != tail)
  {
    n = (dnode *)malloc(sizeof(dnode));
    if (n)
    {
      n->key = k;
      s->prev->next = n;
      n->prev = s->prev;
      s->prev = n;
      n->next = s;
    }
    else
      printf("Memory allocation had been failed!\n");
  }
  
  return n;
}

int dnode_delete(int k)
{
  dnode *s; s = dnode_find(k);
  if (s != tail)
  {
    s->prev->next = s->next;
    s->next->prev = s->prev;
    free(s);
    return 1; 
  }
  
  return 0;
}

dnode *ordered_insert(int k)
{
  dnode *n = NULL;
  dnode *s;
  s = head->next;
  while (s->key <= k && s != tail)
    s = s->next;
  n = (dnode *)malloc(sizeof(dnode)); 
  if (n) 
  {
    n->key = k;  s->prev->next = n;  n->prev = s->prev;  s->prev = n;  n->next = s; 
  }
  else
    printf("Memory allocation had been failed!\n");
  
  return n;
}

void all_dnodes_delete()
{
  dnode *p; dnode *s;
  p = head->next;
  while (p != tail)
  {
    s = p;
    p = p->next;
    free(s);
  }
  head->next = tail;
  tail->prev = head;
}
