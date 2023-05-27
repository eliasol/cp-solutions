#include <iostream>
#include <vector>
#include <sstream>

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

	std::vector<int> vis(n + 1, false);

	auto dfs = [&](int x, auto dfs) -> void {
		for (int c : graph[x])
			if (!vis[c])
				vis[c] = true, dfs(c, dfs);
	};

	int count = 1;
	int last = 1;
	std::stringstream ans;

	dfs(1, dfs);

	for (int i = 2; i <= n; ++i)
		if (!vis[i])
			dfs(i, dfs), ans << last << " " << i << "\n", last = i, ++count;

	std::cout << count - 1 << "\n" << ans.rdbuf();
	return 0;
}
