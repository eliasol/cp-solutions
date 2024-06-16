#include <iostream>
#include <vector>
#include <queue>
#include <functional>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::pair<int, int>>> g(n + 1), gt(n + 1);
	for (int i = 0; i < m; ++i)
	{
		int a, b, x;
		std::cin >> a >> b >> x;
		g[a].push_back({ b, x });
		gt[b].push_back({ a, x });
	}
	std::vector<int> cnt(n + 1, 0);
	std::vector<bool> vis(n + 1, false);
	std::function<void(const std::vector<std::vector<std::pair<int, int>>>&, int)> dfs = [&cnt, &vis, &dfs] (const std::vector<std::vector<std::pair<int, int>>>& g, int x)
	{
		if (vis[x])
			return;
		++cnt[x];
		vis[x] = true;
		for (auto c : g[x])
			dfs(g, c.first);
	};
	dfs(g, 1);
	vis.assign(n + 1, false);
	dfs(gt, n);
	std::vector<long long> dist(n + 1, -1e18);
	dist[1] = 0;
	std::vector<int> cnt2(n + 1, 0);
	std::vector<bool> inqueue(n + 1, false);
	std::queue<int> q;
	q.push(1);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();

		inqueue[x] = false;

		if (cnt2[x] > n)
		{
			std::cout << -1 << std::endl;
			return 0;
		}

		for (auto c : g[x])
		{
			if (cnt[c.first] != 2)
				continue;
			long long newdist = dist[x] + c.second;
			if (newdist <= dist[c.first])
				continue;
			dist[c.first] = newdist;
			++cnt2[c.first];
			if (!inqueue[c.first])
				q.push(c.first), inqueue[c.first] = true;
		}
	}

	std::cout << dist[n] << std::endl;
}
