#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

constexpr int MAXK = 2001;
constexpr int INF = 1e9+1;

int main()
{
	int n;
	std::cin >> n;

	std::vector<int> h(n);
	for (int& i : h) std::cin >> i;

	std::vector<std::vector<int>> inc(n, std::vector<int>(MAXK + 1));
	std::vector<std::vector<int>> dec(n, std::vector<int>(MAXK + 1));
	std::vector<std::vector<int>> inc_suffix(n, std::vector<int>(MAXK + 2));
	std::vector<std::vector<int>> dec_prefix(n, std::vector<int>(MAXK + 2));

	for (int i = 0; i <= MAXK; ++i)
	{
		int x = std::abs(i - h[0]);
		inc[0][i] = dec[0][i] = x*x;
	}

	for (int i = 1; i < n; ++i)
	{
		dec_prefix[i-1][0] = INF;
		for (int j = 1; j <= MAXK; ++j)
		{
			dec_prefix[i-1][j] = std::min(dec_prefix[i-1][j-1], dec[i-1][j-1]);
		}
		inc_suffix[i-1][MAXK + 1] = INF;
		for (int j = MAXK; j >= 0; --j)
		{
			inc_suffix[i-1][j] = std::min(inc_suffix[i-1][j+1], inc[i-1][j]);
		}

		for (int j = 0; j <= MAXK; ++j)
		{
			int x = std::abs(j - h[i]);
			inc[i][j] = dec_prefix[i-1][j] + x*x;
			dec[i][j] = inc_suffix[i-1][j+1] + x*x;
		}
	}

	int ans = 1e9+1;
	for (int i = 0; i <= MAXK; ++i)
		ans = std::min({ans, inc[n-1][i], dec[n-1][i]});

	std::cout << ans << "\n";
	return 0;
}
