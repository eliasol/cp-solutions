#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <optional>

int main()
{
	int n, m;
	std::cin >> n >> m;

	std::vector<std::vector<int>> g(n + 1);

	for (int i = 0; i < m; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	std::vector<std::pair<int, int>> ans;

	std::vector<bool> vis(n + 1, false);
	std::vector<int> height(n + 1);

	std::function<std::optional<int>(int,int,int)> dfs = [&] (int x, int p, int h) -> std::optional<int>
	{
		height[x] = h;
		vis[x] = true;
		int min = 1e9;
		for (int c : g[x])
		{
			if (c == p || vis[c] && height[c] > h)
				continue;
			ans.push_back({x, c});
			std::optional<int> tmp = vis[c] ? height[c] : dfs(c, x, h + 1);
			if (!tmp || tmp > h)
				return {};
			min = std::min(min, tmp.value());
		}
		return min <= h ? min : std::optional<int>();
	};

	if (dfs(1, -1, 0) && std::find(vis.begin() + 1, vis.end(), false) == vis.end())
		for (auto [a, b] : ans)
			std::cout << a << ' ' << b << '\n';
	else
		std::cout << "IMPOSSIBLE\n";
}
