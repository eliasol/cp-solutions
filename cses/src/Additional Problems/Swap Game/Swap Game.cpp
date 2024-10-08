#include <iostream>
#include <queue>
#include <bitset>
#include <utility>

int tenpows[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };
std::bitset<1<<30> vis;

int main()
{
	int x = 0;

	for (int i = 0; i < 9; ++i)
	{
		int k;
		std::cin >> k;
		x = (10 * x) + k;
	}

	vis.set(x);

	std::queue<std::pair<int, int>> q;
	q.push({ x, 0 });

	while (!q.empty())
	{
		auto [x, dist] = q.front();
		q.pop();

		if (x == 123456789)
			return std::cout << dist << std::endl, 0;

		for (int i = 0; i < 9; ++i)
		{
			int digit = (x / tenpows[i]) % 10;

			if (i >= 3)
			{
				int digit2 = (x / tenpows[i - 3]) % 10;
				int sus = x + (digit2 - digit) * tenpows[i] + (digit - digit2) * tenpows[i - 3];
				if (!vis[sus])
					q.push({ sus, dist + 1 }), vis.set(sus);
			}
			if (i <= 5)
			{
				int digit2 = (x / tenpows[i + 3]) % 10;
				int sus = x + (digit2 - digit) * tenpows[i] + (digit - digit2) * tenpows[i + 3];
				if (!vis[sus])
					q.push({ sus, dist + 1 }), vis.set(sus);
			}
			if (i % 3 != 0)
			{
				int digit2 = (x / tenpows[i - 1]) % 10;
				int sus = x + (digit2 - digit) * tenpows[i] + (digit - digit2) * tenpows[i - 1];
				if (!vis[sus])
					q.push({ sus, dist + 1 }), vis.set(sus);
			}
			if (i % 3 != 2)
			{
				int digit2 = (x / tenpows[i + 1]) % 10;
				int sus = x + (digit2 - digit) * tenpows[i] + (digit - digit2) * tenpows[i + 1];
				if (!vis[sus])
					q.push({ sus, dist + 1 }), vis.set(sus);
			}
		}
	}
}
