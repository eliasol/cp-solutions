#include <vector>
#include <assert.h>
#include <malloc.h>
#include <math.h>

#define ALLOC_SIZE 10000000

typedef struct node node;

struct node
{
	int sum;
	node *l, *r;
};

int alloc_i = 0;
node *prealloc;

void initalloc()
{
	prealloc = (node*) malloc(ALLOC_SIZE * sizeof(node));
}

node* alloc()
{
	assert(alloc_i < ALLOC_SIZE);
	return prealloc + (alloc_i++);
}

int n;
node **roots;

node* build(int l, int r)
{
	node *t = alloc();
	if (l == r)
	{
		t->sum = 0;
		t->l = t->r = 0;
		return t;
	}
	int m = (l+r)/2;
	t->l = build(l,m);
	t->r = build(m+1,r);
	t->sum = 0;
	return t;
}

int sum(node *v, int l, int r, int a, int b)
{
	if (a <= l && b >= r) return v->sum;
	int ans = 0, m = (l+r)/2;
	if (a <= m) ans += sum(v->l,l,m,a,b);
	if (b > m) ans += sum(v->r,m+1,r,a,b);
	return ans;
}

node* set(node *v, int l, int r, int x, int k)
{
	if (l == r)
	{
		node *t = alloc();
		t->sum = k;
		t->l = t->r = 0;
		return t;
	}
	int m = (l+r)/2;
	node *t = alloc();
	t->l = x <= m ? set(v->l,l,m,x,k) : v->l;
	t->r = x > m ? set(v->r,m+1,r,x,k) : v->r;
	t->sum = t->l->sum + t->r->sum;
	return t;
}

using namespace std;

void init(int _n) {
	initalloc();
	roots = (node**) malloc((_n+1)*sizeof(node*));
	n = 1 << (int)ceil(log2(_n));
	roots[0] = build(0, n-1);
}

int day = 0;

void log(vector<int>& added, vector<int>& removed) {
	++day;
	roots[day] = roots[day-1];
	for (auto &i : added) roots[day] = set(roots[day],0,n-1,i,1);
	for (auto &i : removed) roots[day] = set(roots[day],0,n-1,i,0);
}

int answer(int d, int x) {
	return sum(roots[d],0,n-1,x,n-1);
}
