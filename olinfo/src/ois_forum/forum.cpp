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

struct segment_tree
{
	int size;
	vector<int> data;

	segment_tree(int n)
	{
		size = 1 << (int)ceil(log2(n));
		data.resize(2*size,0);
	}

	void push(int x) 
	{
		if (data[x])
			data[2*x] = data[2*x+1] = data[x];
		data[x] = 0;
	}

	void set(int a, int b, int v, int x, int l, int r)
	{
		if (r < a || l > b) return;
		if (l >= a && r <= b)
		{
			data[x] = v;
			return;
		}
		push(x);
		set(a,b,v,2*x,l,(l+r)/2);
		set(a,b,v,2*x+1,(l+r)/2+1,r);
	}

	int get(int a, int x, int l, int r)
	{
		if (l > a || r < a) return 0;
		if (l == r) return data[x] == 1;
		push(x);
		return get(a,2*x,l,(l+r)/2) + get(a,2*x+1,(l+r)/2+1,r);
	}
};

vector<vector<int>> graph;
vector<int> topen, tclose;

int Time = 0;

void dfs(int x)
{
	topen[x] = ++Time;
	for (auto &child : graph[x])
		if (!topen[child]) dfs(child);
	tclose[x] = ++Time;
}

int main()
{
	init_io();

	int d,p,e; cin >> d >> p >> e;
	int n = d+p;

	graph.resize(n);
	topen.resize(n,0);
	tclose.resize(n,0);

	for (int i = 0; i < n; ++i)
	{
		int parent; cin >> parent;
		if (i == 0) continue;
		graph[parent].push_back(i);
	}

	dfs(0);

	segment_tree st(2*n);

	while (e--)
	{
		int t,a; cin >> t >> a;
		switch (t)
		{
			case 0:
				st.set(topen[a],tclose[a],-1,1,1,st.size);
				break;
			case 1:
				st.set(topen[a],tclose[a],1,1,1,st.size);
				break;
			case 2:
				cout << (st.get(topen[a],1,1,st.size) == 1 ? 1 : 0) << "\n";
				break;
		}
	}

	return 0;
}
