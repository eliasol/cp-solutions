#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	int n, m;
	std::cin >> n >> m;

	int st_size = 1;
	while (st_size < n)
		st_size *= 2;

	std::vector<int> st(2 * st_size, 0);

	for (int i = 0; i < n; ++i)
		std::cin >> st[st_size + i];

	for (int i = st_size - 1; i > 0; --i)
		st[i] = std::max(st[2 * i], st[2 * i + 1]);

	while (m--)
	{
		int x;
		std::cin >> x;

		int i = 1;

		while (i < st_size)
		{
			if (st[2 * i] >= x)
				i = 2 * i;
			else
				i = 2 * i + 1;
		}

		if (st[i] < x)
		{
			std::cout << "0 ";
			continue;
		}

		std::cout << i - st_size + 1 << " ";

		st[i] -= x;
		for (int j = i / 2; j > 0; j /= 2)
			st[j] = std::max(st[2 * j], st[2 * j + 1]);
	}
}
