#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph, tree;
vector<int> open, close, back;
int t = 0;

void dfs(int x, int p)
{
	open[x] = back[x] = ++t;
	for (int c : graph[x])
	{
		if (c == p)
			continue;
		if (open[c])
			back[x] = min(back[x], open[c]);
		else
		{
			dfs(c, x);
			tree[x].push_back(c);
			back[x] = min(back[x], back[c]);
		}
	}
	close[x] = ++t;
}

int main()
{
	int n, m, q;
	cin >> n >> m >> q;

	graph.resize(n + 1);
	tree.resize(n + 1);
	open.resize(n + 1, 0);
	close.resize(n + 1, 0);
	back.resize(n + 1, 0);

	while (m--)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	dfs(1, 0);

	while (q--)
	{
		int a, b, c;
		cin >> a >> b >> c;

		if (a == c || b == c)
		{
			cout << "NO" << "\n";
			continue;
		}

		bool ca = (open[a] > open[c] && close[a] < close[c]);
		bool cb = (open[b] > open[c] && close[b] < close[c]);

		if (!ca && !cb)
		{
			cout << "YES" << "\n";
			continue;
		}
		
		int treea = -1, treeb = -1;

		if (ca)
		{
			int l = 0, r = tree[c].size();
			while (r - l > 1)
			{
				int m = (l+r)/2;
				if (open[a] < open[tree[c][m]])
					r = m;
				else
					l = m;
			}
			treea = l;
		}
		if (cb)
		{
			int l = 0, r = tree[c].size();
			while (r - l > 1)
			{
				int m = (l+r)/2;
				if (open[b] < open[tree[c][m]])
					r = m;
				else
					l = m;
			}
			treeb = l;
		}

		if (treea < treeb)
			swap(treea, treeb), swap(ca, cb), swap(a, b);
		
		if (!cb && back[tree[c][treea]] < open[c])
		{
			cout << "YES" << "\n";
			continue;
		}
		if (ca && cb && treea != treeb && (back[tree[c][treea]] >= open[c] || back[tree[c][treeb]] >= open[c]))
		{
			cout << "NO" << "\n";
			continue;
		}
		if (ca && cb)
		{
			cout << "YES" << "\n";
			continue;
		}
		cout << "NO" << "\n";
	}
}
