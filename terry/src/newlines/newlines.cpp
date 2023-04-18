#include <iostream>
#include <vector>
#include <utility>

int main()
{
	int T;
	std::cin >> T;

	for (int i = 1; i <= T; ++i)
	{
		int N;
		std::cin >> N;
		std::vector<int> v(N);
		std::pair<int, int> ans = {0, 1e9};
		for (int& i : v)
			std::cin >> i;
		int len = -1;
		for (int i = 0; i < N; ++i)
		{
			if (v[i] != -1)
			{
				len += v[i] + 1;
				continue;
			}
			ans.first = std::max(ans.first, len);
			ans.second = std::min(ans.second, len + v[i + 1]);
			len = -1;
		}
		ans.first = std::max(ans.first, len);
		std::cout << "Case #" << i << ": " << ans.first << " " << ans.second << "\n";
	}

	return 0;
}
