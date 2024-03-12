#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

int main()
{
	int N;
	std::cin >> N;
	std::vector<int> H(N);
	for (int& i : H)
		std::cin >> i;

	H.push_back(0);

	std::vector<std::vector<int>> g(N + 1);

	for (int i = 0; i < N; ++i)
	{
		int x;
		std::cin >> x;
		if (!x)
			g[N].push_back(i);
		while (x--)
		{
			int y;
			std::cin >> y;
			g[y].push_back(i);
		}
	}

	std::vector<bool> vis(N + 1, false);
	std::vector<int> dp(H);

	std::function<void(int)> dfs = [&] (int x) -> void
	{
		if (vis[x])
			return;
		vis[x] = true;
		for (int c : g[x])
			dfs(c), dp[x] = std::max(dp[x], dp[c] + H[x]);
	};

	dfs(N);

	for (int i = 0; i < N; ++i)
		std::cout << dp[N] - dp[i] << " ";
	std::cout << std::endl;
}
