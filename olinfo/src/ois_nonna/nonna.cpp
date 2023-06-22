#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int N, K;
	fin >> N >> K;
	std::vector<int> v(N);
	for (int& i : v)
		fin >> i;
	std::vector<int> dp(K + 1, 1e9);
	dp[0] = 0;
	for (int i = 0; i < N; ++i)
		for (int j = K; j > 0; --j)
			dp[j] = std::min(dp[j], (j >= v[i] ? dp[j - v[i]] : 0) + v[i]);
	fout << dp[K] << std::endl;
	return 0;
}
