#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
	int N, K;
	std::cin >> N >> K;
	std::vector<int> v(N);
	for (int& i : v)
		std::cin >> i;
	std::vector<int> dp(K + 1, 1e9);
	dp[0] = 0;
	for (int i = 0; i < N; ++i)
		for (int j = K; j > 0; --j)
			dp[j] = std::min(dp[j], (j >= v[i] ? dp[j - v[i]] : 0) + v[i]);
	std::cout << (dp[K] == 1e9 ? std::accumulate(v.begin(), v.end(), 0) : dp[K]) << std::endl;
	return 0;
}
