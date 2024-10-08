#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

typedef int& (*sussone)(std::tuple<int, int, int>&);

int main()
{
	int n, x;
	std::cin >> n >> x;

	std::vector<std::tuple<int, int, int>> books(n);

	for (sussone i : { (sussone) &std::get<0, int, int, int>, (sussone) &std::get<1, int, int, int>, (sussone) &std::get<2, int, int, int> })
		for (std::tuple<int, int, int>& j : books)
			std::cin >> i(j);

	for (auto& [h, s, k] : books)
		std::cin >> h >> s >> k;

	std::vector<int> dp(x + 1);


	for (auto [h, s, k] : books)
	{
		int sus = 1, sum = 1;
		for (; sum <= k; sus = std::min(std::max(1, k - sum), sus << 1), sum += sus)
		{
			for (int i = x; i >= h * sus; --i)
			{
				dp[i] = std::max(dp[i], dp[i - h * sus] + s * sus);
			}
		}
		std::cerr << std::endl;
	}

	std::cout << dp.back() << std::endl;
}
