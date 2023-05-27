#include <iostream>
#include <vector>

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

	std::vector<bool> vis(n + 1, false);
	std::vector<int> path;
	bool unroll = false;

	auto dfs = [&](int x, int p, auto dfs) -> bool {
		if (vis[x])
		{
			path.push_back(x);
			unroll = true;
			return true;
		}
		vis[x] = true;
		for (int c : graph[x])
		{
			if (unroll)
				break;
			if (c == p)
				continue;
			if (dfs(c, x, dfs))
			{
				path.push_back(x);
				if (x != path[0])
					return true;
			}
		}
		return false;
	};

	for (int i = 1; i <= n && path.empty(); ++i)
		if (!vis[i])
			dfs(i, -1, dfs);

	if (!path.empty())
	{
		std::cout << path.size() << "\n";
		for (int x : path)
			std::cout << x << " ";
	}
	else
		std::cout << "IMPOSSIBLE\n";
	return 0;
}
