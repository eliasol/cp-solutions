#include <iostream>

int main()
{
	int T;
	std::cin >> T;

	for (int t = 1; t <= T; ++t)
	{
		int N, K;
		std::cin >> N >> K;
		int ans = 0;
		while (N > 0)
		{
			ans += N;
			N /= K;
		}
		std::cout << "Case #" << t << ": " << ans << "\n";
	}
}
