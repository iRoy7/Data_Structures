#include <stdio.h>
#include <stdlib.h>
const int NHEAP = 100000;

typedef int prior_fnc(int d1, int d2);
typedef struct _heap {
	prior_fnc *cmp;
	int num;
	int heapnodes[NHEAP];
} heap;

void h_init(heap *ph, prior_fnc pf)
{
	ph->num = 0;
	ph->cmp = pf;
}

int is_empty(heap *ph)
{
	return (ph->num == 0) ? 1 : 0;
}

int parent_id_get(int cid)
{
	return cid / 2;
}

int lch_id_get(int pid)
{
	return pid * 2;
}

int rch_id_get(int pid)
{
	return pid * 2 + 1;
}

int hprior_child_id_get(heap *ph, int pid)
{
	if (lch_id_get(pid) > ph->num)
		return 0;
	else if (lch_id_get(pid) == ph->num)
		return lch_id_get(pid);
	else
	{
		if (ph->cmp(
			ph->heapnodes[lch_id_get(pid)],
			ph->heapnodes[rch_id_get(pid)]) < 0)
			return rch_id_get(pid);
		else
			return lch_id_get(pid);
	}
}

void h_insert(heap *ph, int key)
{// PUSH
	int id = ph->num + 1;

	while (id != 1)
	{
		if (ph->cmp(key,
			ph->heapnodes[parent_id_get(id)]) > 0)
		{
			ph->heapnodes[id] = ph->heapnodes[parent_id_get(id)];
			id = parent_id_get(id);
		}
		else
			break;
	}

	ph->heapnodes[id] = key;
	ph->num += 1;
}

int h_delete(heap *ph)
{// POP
	int ret = ph->heapnodes[1];

	int lastv = ph->heapnodes[ph->num];
	int p_id = 1;
	int ch_id;

	while (ch_id = hprior_child_id_get(ph, p_id))
	{
		if (ph->cmp(lastv,
			ph->heapnodes[ch_id]) >= 0)
			break;

		ph->heapnodes[p_id] = ph->heapnodes[ch_id];
		p_id = ch_id;
	}

	ph->heapnodes[p_id] = lastv;
	ph->num -= 1;

	return ret;
}

int h_delete_v(heap *ph, int key)
{//KEY DELETE
	// Search key's id
	int id = 0;
	for (int i = 1; i <= ph->num; i++)
	{
		if (key == ph->heapnodes[i])
			id = i;
	}

	int ret = 0;
	if (id) ret = ph->heapnodes[id];
	else return (-1);

	int lastv = ph->heapnodes[ph->num];
	int p_id = id;
	int ch_id;

	while (ch_id = hprior_child_id_get(ph, p_id))
	{
		if (ph->cmp(lastv,
			ph->heapnodes[ch_id]) >= 0)
			break;

		ph->heapnodes[p_id] = ph->heapnodes[ch_id];
		p_id = ch_id;
	}

	ph->heapnodes[p_id] = lastv;
	ph->num -= 1;

	return ret;
}

const int QMAX = 100000;
int heapids[QMAX];
int head = -1, tail = -1;
void qinit(void)
{
	head = tail = -1;
	for (int i = 0; i < QMAX; i++)
		heapids[i] = 0;
}

void h_traverse(heap *ph)
{
	if (ph == NULL) return;
	qinit();

	heapids[++tail] = 1;

	while (tail != head)
	{
		int id = heapids[++head];
		if (id > ph->num) break;
		printf("id = (%d), key = (%d)\n", id, ph->heapnodes[id]);

		if (lch_id_get(id)) heapids[++tail] = lch_id_get(id);
		if (rch_id_get(id)) heapids[++tail] = rch_id_get(id);
	}
}

void h_node_clean(heap *ph)
{
	for (int i = 0; i < NHEAP; i++)
		ph->heapnodes[i] = -1;
}

int h_top_get(heap *ph)
{
	return ph->heapnodes[1];
}

int h_num_get(heap *ph)
{
	return ph->num;
}