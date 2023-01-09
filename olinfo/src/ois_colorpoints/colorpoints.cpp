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

#define START_X 0
#define START_Y (1e6+1)
#define SOURCE (2e6+2)
#define SINK (2e6+3)

void no_sol()
{
	cout << "No" << "\n";
	exit(0);
}

int n;

struct edge
{
	int from;
	int to;
	int weight;
	int flow;
};

vector<edge> edges;
vector<vector<int>> graph(2e6+4);
vector<bool> vis(2e6+4,0);

inline int back_edge(int i) { return i^1; }

void add_edge(int from, int to, int weight)
{
	edges.push_back({from,to,weight,0});
	edges.push_back({to,from,weight,weight});
	graph[from].push_back(edges.size()-2);
	graph[to].push_back(edges.size()-1);
}

int dfs(int x, int flow)
{
	if (x == SINK) return flow;
	vis[x] = 1;
	for (int i = 0; i < graph[x].size(); ++i)
	{
		edge& e = edges[graph[x][i]];
		if (e.flow == e.weight || vis[e.to]) continue;
		int sent = dfs(e.to, min(flow, e.weight - e.flow));

		if (sent > 0)
		{
			e.flow += sent;
			edges[back_edge(graph[x][i])].flow -= sent;
			return sent;
		}
	}
	return 0;
}

void maxflow()
{
	while (dfs(SOURCE,INT_MAX))
		for (auto& e : edges)
			vis[e.from] = 0, vis[e.to] = 0;
}

int main()
{
	init_io();

	cin >> n;

	vector<int> xs(1e6+1,0), ys(1e6+1,0);

	for (int i = 0; i < n; ++i)
	{
		int x,y; cin >> x >> y;
		++xs[x], ++ys[y];
		add_edge(START_X + x, START_Y + y, 1);
	}

	for (int i = 0; i < xs.size(); ++i)
	{
		if (!xs[i]) continue;
		if (xs[i]%3) no_sol();
		add_edge(SOURCE, START_X + i, xs[i]/3);
	}

	for (int i = 0; i < ys.size(); ++i)
	{
		if (!ys[i]) continue;
		if (ys[i]%3) no_sol();
		add_edge(START_Y + i, SINK, ys[i]/3);
	}

	maxflow();

	cout << "Yes\n" << n/3 << "\n";

	for (edge& e : edges)
	{
		if (e.from == SOURCE || e.to == SINK || e.from >= START_Y) continue;
		if (e.flow) cout << e.from - START_X << " " << e.to - START_Y << "\n";
	}

	return 0;
}
