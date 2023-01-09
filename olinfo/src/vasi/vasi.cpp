#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define init_io() cin.sync_with_stdio(0); cin.tie(0); cout.sync_with_stdio(0); cout.tie(0)

#define FILE_IO_LOCAL 1
#define FILE_IO_JUDGE 1

#if FILE_IO_LOCAL && !defined(EVAL) || FILE_IO_JUDGE && defined(EVAL)
ifstream fin("input.txt");
ofstream fout("output.txt");
#define cin fin
#define cout fout
#endif

struct treap
{
	int id;
	int priority;
	int size = 1;
	treap* l;
	treap* r;

	treap() {}
	treap(int p_id) : id(p_id), priority(rand()) {}
};

treap arr[400000];
int i_alloc = 0;

treap* alloc(int id)
{
	assert(i_alloc < 400000);
	new (arr+i_alloc) treap(id);
	return arr+(i_alloc++);
}

treap* root;

void update(treap* node)
{
	if (!node) return;
	node->size = (node->l ? node->l->size : 0) + (node->r ? node->r->size : 0) + 1;
}

treap* build(int a, int b)
{
	if (a > b) return 0;
	int mid = (a+b)/2;
	treap* node = alloc(mid);
	node->l = build(a,mid-1);
	node->r = build(mid+1,b);
	update(node);
	return node;
}

void heapify(treap* node)
{
	if (!node) return;
	treap* high = node;
	if (node->l && node->l->priority > high->priority) high = node->l;
	if (node->r && node->r->priority > high->priority) high = node->r;
	if (high != node) swap(high->priority, node->priority);
	heapify(node->l);
	heapify(node->r);
}

treap* merge(treap* a, treap* b)
{
	if (!a) return b;
	if (!b) return a;
	if (a->priority > b->priority)
	{
		a->r = merge(a->r,b);
		update(a);
		return a;
	}
	else
	{
		b->l = merge(a,b->l);
		update(b);
		return b;
	}
}

pair<treap*,treap*> split(treap* node, int k)
{
	if (!node) return {0,0};
	int sizel = node->l ? node->l->size : 0;
	if (k < sizel)
	{
		auto tmp = split(node->l, k);
		node->l = tmp.second;
		update(tmp.first);
		update(node);
		return {tmp.first,node};
	}
	else if (k == sizel)
	{
		treap* tmp = node->l;
		node->l = 0;
		update(tmp);
		update(node);
		return {tmp,node};
	}
	else
	{
		auto tmp = split(node->r, k-sizel-1);
		node->r = tmp.first;
		update(node);
		update(tmp.second);
		return {node,tmp.second};
	}
}

int find(treap* node, int k)
{
	int sizel = node->l ? node->l->size : 0;
	if (k == sizel) return node->id;
	else if (k < sizel) return find(node->l,k);
	else return find(node->r, k-sizel-1);
}

void insert(treap* node, int k)
{
	auto tmp = split(root,k);
	root = merge(merge(tmp.first,node),tmp.second);
}

treap* erase(int k)
{
	auto tmp = split(root,k);
	auto tmp2 = split(tmp.second,1);
	root = merge(tmp.first,tmp2.second);
	return tmp2.first;
}

int main()
{
	init_io();

	int n,q; cin >> n >> q;

	root = build(0,n-1);
	heapify(root);

	while (q--)
	{
		char c; cin >> c;
		if (c == 'c')
		{
			int x; cin >> x;
			cout << find(root,x) << " ";
		}
		else
		{
			int a,b; cin >> a >> b;
			treap* t = erase(a);
			insert(t,b);
		}
	}

	return 0;
}
