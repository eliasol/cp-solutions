#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

constexpr int INF = 1e9;

int solve()
{
	int N, M, X, Y;
	std::cin >> N >> M >> X >> Y;
	std::array<std::vector<std::pair<int, int>>, 'z' - 'a' + 1> edges;
	for (int i = 0; i < M; ++i)
	{
		int A, B;
		char L;
		std::cin >> A >> B >> L;
		edges[L - 'a'].push_back({A, B});
	}
	std::vector<std::vector<int>> graph(N * N);
	for (const std::vector<std::pair<int, int>>& i : edges)
	{
		for (size_t j = 0; j < i.size(); ++j)
		{
			for (size_t k = 0; k < i.size(); ++k)
			{
				if (j == k)
					continue;
				graph[N * i[j].first + i[k].first].push_back(N * i[j].second + i[k].second);
				graph[N * i[j].second + i[k].second].push_back(N * i[j].first + i[k].first);
				graph[N * i[j].first + i[k].second].push_back(N * i[j].second + i[k].first);
				graph[N * i[j].second + i[k].first].push_back(N * i[j].first + i[k].second);
			}
		}
	}
	std::vector<int> distance(N * N, INF);
	std::queue<int> queue;

	distance[N * X + Y] = 0;
	queue.push(N * X + Y);

	while (!queue.empty())
	{
		int current = queue.front();
		queue.pop();
		for (int child : graph[current])
		{
			if (distance[child] <= distance[current] + 1)
				continue;
			distance[child] = distance[current] + 1;
			queue.push(child);
		}
	}

	int ans = INF;
	for (int i = 0; i < N; ++i)
		ans = std::min(ans, 2 * distance[N * i + i]);
	for (const std::vector<std::pair<int, int>>& i : edges)
		for (const std::pair<int, int>& edge : i)
			ans = std::min({ans, 2 * distance[N * edge.first + edge.second] + 1, 2 * distance[N * edge.second + edge.first] + 1});
	return ans == INF ? -1 : ans;
}

int main()
{
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; ++t)
		std::cout << "Case #" << t << ": " << solve() << "\n";
	return 0;
}
