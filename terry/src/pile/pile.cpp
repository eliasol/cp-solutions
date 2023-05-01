#include <iostream>
#include <algorithm>

int main()
{
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; ++t)
	{
		int N;
		std::cin >> N;
		int sum = 0;
		while (N--)
		{
			int a, b, c;
			std::cin >> a >> b >> c;
			sum += std::max({a, b, c});
		}
		std::cout << "Case #" << t << ": " << sum << "\n";
	}
	return 0;
}
