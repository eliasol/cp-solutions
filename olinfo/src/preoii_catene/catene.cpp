#include <vector>
#include <array>
#include <utility>
#include <functional>
#include <algorithm>

long long profitto_massimo(int N, int U[], int V[], int W[])
{
	std::vector<std::vector<std::pair<int, int>>> g(N + 1);

	for (int i = 0; i < N - 1; ++i)
		g[U[i]].push_back({ V[i], W[i] }), g[V[i]].push_back({ U[i], W[i] });

	std::function<std::array<long long, 3>(int,int)> dfs = [&dfs, &g] (int x, int p) -> std::array<long long, 3>
	{
		int best1 = 0, best2 = 0;
		long long sum = 0;
		for (auto& [c, w] : g[x])
		{
			if (c == p)
				continue;
			std::array<long long, 3> dp = dfs(c, x);
			sum += dp[1];
			best2 = std::max(best2, (int) (dp[0] - dp[1] + w));
			if (best2 > best1)
				std::swap(best1, best2);
		}

		return { sum + best1, sum + best1 + best2 };
	};

	return dfs(1, -1)[1];
}
