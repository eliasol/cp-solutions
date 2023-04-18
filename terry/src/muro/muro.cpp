#include <iostream>

int main()
{
	int T;
	std::cin >> T;

	for (int i = 1; i <= T; ++i)
	{
		int N, Q;
		std::cin >> N >> Q;
		int x = 0;
		while (Q--)
		{
			int l;
			std::cin >> l;
			x = std::min(x, N - l);
			++x;
		}
		std::cout << "Case #" << i << ": " << x << "\n";
	}

	return 0;
}
