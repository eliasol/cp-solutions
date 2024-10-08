#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main()
{
	int n;
	std::cin >> n;

	std::priority_queue<std::pair<int, int>> pq;

	for (int i = 1; i <= n; ++i)
	{
		int x;
		std::cin >> x;

		if (x > 0)
			pq.push({ x, i });
	}

	std::vector<std::pair<int, int>> ans;
	std::vector<std::pair<int, int>> toins;

	while (!pq.empty())
	{
		auto [games, x] = pq.top();
		pq.pop();

		if (games > pq.size())
			return std::cout << "IMPOSSIBLE\n", 0;

		while (games--)
		{
			auto [games2, x2] = pq.top();
			pq.pop();

			ans.push_back({ x, x2 });
			if (games2 > 1)
				toins.push_back({ games2 - 1, x2 });
		}

		while (!toins.empty())
		{
			pq.push(toins.back());
			toins.pop_back();
		}
	}

	std::cout << ans.size() << "\n";

	for (auto [x, y] : ans)
		std::cout << x << " " << y << "\n";
}
