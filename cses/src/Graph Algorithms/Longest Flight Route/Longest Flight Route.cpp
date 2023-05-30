#include <iostream>
#include <vector>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> dag(n + 1);
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		dag[a].push_back(b);
	}

	std::vector<int> next(n + 1, 0), dp(n + 1, -1);
	dp[n] = 1;

	auto dfs = [&](int x, auto dfs) -> int
	{
		if (dp[x] != -1)
			return dp[x];
		int best = 0, besti = 0;
		for (int c : dag[x])
		{
			int tmp = dfs(c, dfs);
			if (tmp == 0)
				continue;
			if (tmp + 1 > best)
				best = tmp + 1, besti = c;
		}
		next[x] = besti;
		return dp[x] = best;
	};

	if (dfs(1, dfs) == 0)
	{
		std::cout << "IMPOSSIBLE\n";
		return 0;
	}

	std::cout << dp[1] << "\n";

	int curr = 1;
	while (curr)
	{
		std::cout << curr << " ";
		curr = next[curr];
	}
	return 0;
}
