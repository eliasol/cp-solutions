#include <iostream>
#include <vector>
#include <utility>
#include <queue>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::pair<int, int>>> graph(2 * n + 1);
	for (int i = 0; i < m; ++i)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		graph[a].push_back({b, c});
		graph[n + a].push_back({n + b, c});
		graph[a].push_back({n + b, c / 2});
	}

	std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;
	std::vector<bool> vis(2 * n + 1, false);

	pq.push({0, 1});

	while (!pq.empty())
	{
		auto [dist, x] = pq.top();
		pq.pop();
		if (vis[x])
			continue;
		vis[x] = true;
		if (x == 2 * n)
		{
			std::cout << dist << "\n";
			return 0;
		}
		for (const auto& c : graph[x])
			pq.push({dist + c.second, c.first});
	}
}
