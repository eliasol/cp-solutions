#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n;
	cin >> n;

	vector<vector<pair<int, int>>> graph(2*n + 2);
	vector<int> edges;
	vector<bool> vis;

	auto add_edge = [&graph, &edges](int a, int b, int c) -> void {
		graph[a].emplace_back(b, edges.size());
		edges.push_back(c);
		graph[b].emplace_back(a, edges.size());
		edges.push_back(0);
	};

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			char c;
			cin >> c;
			if (c == '.')
				continue;
			add_edge(i, n + j, 1e9);
		}
	}

	for (int i = 0; i < n; ++i)
	{
		add_edge(2*n, i, 1);
		add_edge(n + i, 2*n + 1, 1);
	}

	auto dfs = [&graph, &edges, &vis](int x, int sink, int flow, auto dfs) -> int {
		vis[x] = true;
		if (x == sink)
			return flow;
		for (auto& c : graph[x])
		{
			if (edges[c.second] == 0 || vis[c.first])
				continue;
			int newflow = dfs(c.first, sink, min(flow, edges[c.second]), dfs);
			if (newflow == 0)
				continue;
			edges[c.second] -= newflow;
			edges[c.second ^ 1] += newflow;
			return newflow;
		}
		return 0;
	};

	auto max_flow = [&graph, &edges, &dfs, &vis](int source, int sink) -> int {

		int flow = 0;
		int x;
		while ((x = dfs(source, sink, 1e9, dfs)) > 0)
			flow += x, fill(vis.begin(), vis.end(), false);
		return flow;
	};

	vis.resize(graph.size(), false);
	cout << max_flow(2*n, 2*n + 1) << "\n";

	auto dfs2 = [&graph, &edges, &vis](int x, auto dfs2) -> void {
		vis[x] = true;
		for (auto& c : graph[x])
		{
			if (vis[c.first] || edges[c.second] == 0)
				continue;
			dfs2(c.first, dfs2);
		}
	};

	fill(vis.begin(), vis.end(), false);
	dfs2(2*n, dfs2);

	for (int i = 0; i < n; ++i)
		if (!vis[i])
			cout << 1 << " " << i + 1 << "\n";
	for (int i = 0; i < n; ++i)
		if (vis[n + i])
			cout << 2 << " " << i + 1 << "\n";
	return 0;
}
