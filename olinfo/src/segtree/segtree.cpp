#include <vector>
#include <math.h>
#include <malloc.h>
#include <limits.h>

using namespace std;

const long long INF = LLONG_MAX;

typedef struct {
	long long sum;
	long long min;
} node;

typedef struct {
	long long add;
	long long set;
} lazy;

int n;
node *st;
lazy *lz;

long long min(long long a, long long b) { return a < b ? a : b; }

inline void merge(int x)
{
	st[x].sum = st[2*x].sum + st[2*x+1].sum;
	st[x].min = min(st[2*x].min, st[2*x+1].min);
}

inline void push(int x, int l, int r)
{
	int m = (l+r)/2;
	if (lz[x].set != INF)
	{
		st[2*x].min = lz[x].set;
		st[2*x].sum = lz[x].set * (m-l+1);
		st[2*x+1].min = lz[x].set;
		st[2*x+1].sum = lz[x].set * (r-m);
		if (m-l)
		{
			lz[2*x].set = lz[2*x+1].set = lz[x].set;
			lz[2*x].add = lz[2*x+1].add = 0;
		}
		lz[x].set = INF;
	}
	if (lz[x].add != 0)
	{
		st[2*x].min += lz[x].add;
		st[2*x].sum += lz[x].add * (m-l+1);
		st[2*x+1].min += lz[x].add;
		st[2*x+1].sum += lz[x].add * (r-m);
		if (m-l)
		{
			lz[2*x].add += lz[x].add;
			lz[2*x+1].add += lz[x].add;
		}
		lz[x].add = 0;
	}
}

long long _get_sum(int a, int b, int x, int l, int r)
{
	if (l >= a && r <= b) return st[x].sum;
	push(x,l,r);
	int m = (l+r)/2;
	long long ans = 0;
	if (a <= m) ans += _get_sum(a,b,2*x,l,m);
	if (b > m) ans += _get_sum(a,b,2*x+1,m+1,r);
	return ans;
}

long long _get_min(int a, int b, int x, int l, int r)
{
	if (l >= a && r <= b) return st[x].min;
	push(x,l,r);
	int m = (l+r)/2;
	long long ans = INF;
	if (a <= m) ans = min(ans,_get_min(a,b,2*x,l,m));
	if (b > m) ans = min(ans,_get_min(a,b,2*x+1,m+1,r));
	return ans;
}

void _add(int a, int b, long long v, int x, int l, int r)
{
	if (l >= a && r <= b)
	{
		if (x >= n)
		{
			st[x].min += v;
			st[x].sum += v;
		}
		else
		{
			lz[x].add += v;
			st[x].min += v;
			st[x].sum += v*(r-l+1);
		}
		return;
	}
	push(x,l,r);
	int m = (l+r)/2;
	if (a <= m) _add(a,b,v,2*x,l,m);
	if (b > m) _add(a,b,v,2*x+1,m+1,r);
	merge(x);
}

void _set(int a, int b, long long v, int x, int l, int r)
{
	if (l >= a && r <= b)
	{
		if (x >= n) st[x].min = st[x].sum = v;
		else
		{
			lz[x].add = 0;
			lz[x].set = v;
			st[x].min = v;
			st[x].sum = v*(r-l+1);
		}
		return;
	}
	push(x,l,r);
	int m = (l+r)/2;
	if (a <= m) _set(a,b,v,2*x,l,m);
	if (b > m) _set(a,b,v,2*x+1,m+1,r);
	merge(x);
}

int _lower_bound(int a, int b, long long v, int x, int l, int r)
{
	if (st[x].min > v) return -1;
	if (x >= n) return l;
	if (l >= a && r <= b)
	{
		while(l != r) 
		{
			push(x,l,r);
			int m = (l+r)/2;
			if(st[2*x].min <= v)
			{
				x = 2*x;
				r = m;
			}
			else 
			{
				x = 2*x+1;
				l = m+1;
			}
		}
		return l;
	}
	push(x,l,r);
	int m = (l+r)/2;
	int ans = -1;
	if (a <= m) ans = _lower_bound(a,b,v,2*x,l,m);
	if (ans == -1 && b > m) ans = _lower_bound(a,b,v,2*x+1,m+1,r);
	return ans;
}

// GRADER'S FUNCTIONS

void init(vector<long long> a) {
	n = 1 << (int) ceil(log2(a.size()));
	st = (node*) malloc(2*n*sizeof(node));
	lz = (lazy*) malloc(n*sizeof(lazy));
	for (int i = 0; i < a.size(); ++i) st[n+i].sum = st[n+i].min = a[i];
	for (int i = a.size(); i < n; ++i)
	{
		st[n+i].sum = 0;
		st[n+i].min = INF;
	}
	for (int i = n-1; i > 0; --i) merge(i);
	for (int i = 0; i < n; ++i)
	{
		lz[i].add = 0;
		lz[i].set = INF;
	}
}

long long get_sum(int l, int r) {
	return _get_sum(l,r-1,1,0,n-1);
}

void add(int l, int r, long long x) {
	_add(l,r-1,x,1,0,n-1);
}

void set_range(int l, int r, long long x) {
	_set(l,r-1,x,1,0,n-1);
}

long long get_min(int l, int r) {
	return _get_min(l,r-1,1,0,n-1);
}

int lower_bound(int l, int r, long long x) {
	return _lower_bound(l,r-1,x,1,0,n-1);
}
