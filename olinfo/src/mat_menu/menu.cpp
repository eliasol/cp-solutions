#include <iostream>
#include <vector>
#include <bitset>

int main()
{
	int N, B;
	std::cin >> N >> B;
	std::vector<int> C(N);
	for (int& i : C)
		std::cin >> i;
	std::vector<std::bitset<5001>> dp(N + 1);
	dp[0][0] = true;
	for (int i = 1; i <= N; ++i)
		dp[i] = dp[i - 1] | (dp[i - 1] << C[i - 1]);
	int i = N, j = [&dp,N,B](){int i; for (i = B; !dp[N][i]; --i); return i;}();
	for (; j != 0; --i)
	{
		if (dp[i][j] == dp[i - 1][j])
			continue;
		std::cout << C[i - 1] << "\n";
		j -= C[i - 1];
	}
	return 0;
}
