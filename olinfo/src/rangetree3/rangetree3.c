#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>

typedef struct {
	int prefix,suffix,sum,sub;
} node;

int sz;
node *st;
node nullnode = { .prefix = (int)-2e9, .suffix = (int)-2e9, .sum = 0, .sub = (int)-2e9 };

inline int max(int a, int b) { return a > b ? a : b; }

node merge(node *n1, node *n2)
{
	node res;
	res.sum = n1->sum + n2->sum;
	res.prefix = max(n1->prefix, n1->sum + n2->prefix);
	res.suffix = max(n2->suffix, n2->sum + n1->suffix);
	res.sub = max(n1->sub, max(n2->sub, n1->suffix + n2->prefix));
	return res;
}

void init(int *v, int n)
{
	sz = 1 << (int)ceil(log2(n));
	st = (node*) malloc(2*sz*sizeof(node));
	for (int i = 0; i < n; ++i) st[sz+i].prefix = st[sz+i].suffix = st[sz+i].sum = st[sz+i].sub = v[i];
	for (int i = sz+n; i < 2*sz; ++i) st[i] = nullnode;
	for (int i = sz-1; i > 0; --i) st[i] = merge(&st[2*i],&st[2*i+1]);
}

void set(int i, int v, int x, int l, int r)
{
	if (l == r)
	{
		st[x].prefix = st[x].suffix = st[x].sum = st[x].sub = v;
		return;
	}
	int m = (l+r)/2;
	if (i <= m) set(i,v,2*x,l,m);
	else set(i,v,2*x+1,m+1,r);
	st[x] = merge(&st[2*x],&st[2*x+1]);
}

node query(int a, int b, int x, int l, int r)
{
	if (a <= l && b >= r) return st[x];
	int m = (l+r)/2;
	node n1 = nullnode, n2 = nullnode;
	if (a <= m) n1 = query(a,b,2*x,l,m);
	if (b > m) n2 = query(a,b,2*x+1,m+1,r);
	return merge(&n1,&n2);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	int n,q;
	scanf("%d", &n);

	int *v = (int*) malloc(n*sizeof(int));
	for (int i = 0; i < n; ++i) scanf("%d", v+i);

	init(v,n);

	scanf("%d", &q);
	for (int i = 0; i < q; ++i)
	{
		int type,x,y;
		scanf("%d %d %d", &type, &x, &y);
		if (type == 0)
		{
			set(x-1,y,1,0,sz-1);
		}
		else
		{
			node tmp = query(x-1,y-1,1,0,sz-1);
			printf("%d\n", tmp.sub);
		}
	}

	free(v);
	free(st);
}
