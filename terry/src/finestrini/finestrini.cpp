#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int solve()
{
	int N;
	std::cin >> N;
	std::vector<std::array<int, 2>> rows(N);
	for (int i = 0; i < N; ++i)
		std::cin >> rows[i][0] >> rows[i][1];
	std::vector<std::array<int, 4>> dp(N);
	dp[0][0] = rows[0][0];
	dp[0][2] = rows[0][1];
	dp[0][1] = dp[0][3] = 1e9;
	for (int i = 1; i < N; ++i)
	{
		dp[i][0] = std::min(dp[i - 1][2], dp[i - 1][3]) + rows[i][0];
		dp[i][1] = dp[i - 1][0] + rows[i][0];
		dp[i][2] = std::min(dp[i - 1][0], dp[i - 1][1]) + rows[i][1];
		dp[i][3] = dp[i - 1][2] + rows[i][1];
	}
	return *std::min_element(dp[N - 1].begin(), dp[N - 1].end());
}

int main()
{
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; ++t)
		std::cout << "Case #" << t << ": " << solve() << "\n";
	return 0;
}
