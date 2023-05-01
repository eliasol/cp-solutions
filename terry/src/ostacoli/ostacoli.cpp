#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>

static constexpr int INF = 1e9 + 1;

int solve()
{
	int N, L, D;
	std::cin >> N >> L >> D;
	std::vector<std::array<int, 3>> V(N + 1);
	V[0] = {0, 0, 0};
	for (int i = 1; i <= N; ++i)
		std::cin >> V[i][0] >> V[i][1] >> V[i][2];
	std::vector<int> dp(N + 1, -INF);
	dp[0] = 0;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (std::abs(V[i][0] - V[j][0]) > V[i][2] - V[j][2])
				continue;
			dp[i] = std::max(dp[i], dp[j] + V[i][1]);
		}
	}
	return *std::max_element(dp.begin(), dp.end());
}

int main()
{
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; ++t)
		std::cout << "Case #" << t << ": " << solve() << "\n";
	return 0;
}
