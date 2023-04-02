#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<pair<int, int>>> graph(n + m + 2);
	vector<int> edges;

	auto add_edge = [&graph, &edges](int a, int b, int c) -> void {
		graph[a].emplace_back(b, edges.size());
		edges.push_back(c);
		graph[b].emplace_back(a, edges.size());
		edges.push_back(0);
	};

	for (int i = 1; i <= n; ++i)
		add_edge(0, i, 1);
	for (int i = n + 1; i <= n + m; ++i)
		add_edge(i, n + m + 1, 1);

	for (int i = 0; i < k; ++i)
	{
		int a, b;
		cin >> a >> b;
		add_edge(a, n + b, 1);
	}

	auto dfs = [&graph, &edges](int x, int sink, int flow, vector<bool>& vis, auto dfs) -> int {
		vis[x] = true;
		if (x == sink)
			return flow;
		for (auto& c : graph[x])
		{
			if (edges[c.second] == 0 || vis[c.first])
				continue;
			int newflow = dfs(c.first, sink, min(flow, edges[c.second]), vis, dfs);
			if (newflow == 0)
				continue;
			edges[c.second] -= newflow;
			edges[c.second ^ 1] += newflow;
			return newflow;
		}
		return 0;
	};

	auto max_flow = [&graph, &edges, &dfs](int source, int sink) -> int {
		vector<bool> vis(graph.size());
		int flow = 0;
		int x;
		while ((x = dfs(source, sink, 1e9, vis, dfs)) > 0)
			flow += x, fill(vis.begin(), vis.end(), false);
		return flow;
	};

	cout << max_flow(0, n + m + 1) << "\n";

	for (int i = 1; i <= n; ++i)
		for (auto& j : graph[i])
			if (j.second % 2 == 0 && edges[j.second] == 0)
				cout << i << " " << j.first - n << "\n";
}
