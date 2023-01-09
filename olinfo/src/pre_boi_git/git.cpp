#include <vector>

using namespace std;

struct node
{
	long long sum;
	long long add;
	node* l;
	node* r;
};

node storage[10000000];
int alloc_i = 0;
node* alloc() { return storage+(alloc_i++); }
node* alloc(const node& x) { storage[alloc_i] = x; return storage+(alloc_i++); }
node* alloc(node&& x) { storage[alloc_i] = x; return storage+(alloc_i++); }

int N;
vector<node*> versions;

node* merge(node* a, node* b)
{
	node* x = alloc();
	x->sum = a->sum + b->sum;
	x->l = a;
	x->r = b;
	return x;
}

void push(node* x, int l, int r)
{
	int m = (l+r)/2;
	if (x->add == 0) return;
	if (x->l)
	{
		node* nl = alloc(*x->l);
		node* nr = alloc(*x->r);
		nl->add += x->add;
		nl->sum += (m-l)*(x->add);
		nr->add += x->add;
		nr->sum += (r-m)*(x->add);
		x->l = nl;
		x->r = nr;
	}
	x->add = 0;
}

node* build(vector<int>& v, int l, int r)
{
	if (l == r-1) return alloc(node{v[l],0});
	int m = (l+r)/2;
	return merge(build(v,l,m), build(v,m,r));
}

node* add(int a, int b, long long v, node* x, int l, int r)
{
	if (b <= l || a >= r) return x;
	if (a <= l && b >= r)
	{
		node* res = alloc(*x);
		res->sum += v*(r-l);
		res->add += v;
		return res;
	}
	push(x,l,r);
	int m = (l+r)/2;;
	return merge(add(a,b,v,x->l,l,m), add(a,b,v,x->r,m,r));
}

long long sum(int a, int b, node* x, int l, int r)
{
	if (b <= l || a >= r) return 0;
	if (a <= l && b >= r) return x->sum;
	push(x,l,r);
	int m = (l+r)/2;
	return sum(a,b,x->l,l,m) + sum(a,b,x->r,m,r);
}

node* reset(int a, int b, node* x1, node* x2, int l, int r)
{
	if (b <= l || a >= r) return x2;
	if (a <= l && b >= r) return x1;
	push(x1,l,r);
	push(x2,l,r);
	int m = (l+r)/2;
	return merge(reset(a,b,x1->l,x2->l,l,m), reset(a,b,x1->r,x2->r,m,r));
}

void inizia(int N, vector<int> A)
{
	::N = N;
	versions.push_back(build(A,0,N));
}

void incrementa(int l, int r, int x)
{
	versions.push_back(add(l,r,x,versions.back(),0,N));
}

void resetta(int l, int r, int v)
{
	versions.push_back(reset(l,r,versions[v],versions.back(),0,N));
}

long long somma(int l, int r)
{
	return sum(l,r,versions.back(),0,N);
}
