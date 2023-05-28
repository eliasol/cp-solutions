#include <iostream>
#include <vector>
#include <cstdlib>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> graph(n + 1);
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	std::vector<bool> vis(n + 1, false), color(n + 1);

	auto dfs = [&](int x, auto dfs) -> void
	{
		for (int c : graph[x])
		{
			if (vis[c] && color[x] == color[c])
			{
				std::cout << "IMPOSSIBLE\n";
				exit(0);
			}
			if (!vis[c])
			{
				vis[c] = true;
				color[c] = !color[x];
				dfs(c, dfs);
			}
		}
	};

	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			dfs(i, dfs);

	for (int i = 1; i <= n; ++i)
		std::cout << color[i] + 1 << " ";
	return 0;
}
