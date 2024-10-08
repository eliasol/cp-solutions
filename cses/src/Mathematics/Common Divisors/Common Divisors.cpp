#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>

int main()
{
	int N;
	std::cin >> N;

	std::vector<int> v(1e6 + 1, 0);

	while (N--)
	{
		int x;
		std::cin >> x;
		for (int i = 1; i * i <= x; ++i)
		{
			if (x % i)
				continue;
			++v[i];
			if (i * i != x)
				++v[x / i];
		}
	}

	for (int i = 1e6; i > 0; --i)
		if (v[i] > 1)
			return std::cout << i << std::endl, 0;
}
