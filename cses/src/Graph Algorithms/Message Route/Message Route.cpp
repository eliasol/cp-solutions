#include <iostream>
#include <vector>
#include <queue>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> graph(n + 1);
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	std::vector<int> prec(n + 1, 0);
	std::queue<std::pair<int, int>> q;
	prec[n] = -1;
	q.push({n, 1});

	while (!q.empty())
	{
		auto [x, dist] = q.front();
		q.pop();
		if (x == 1)
		{
			std::cout << dist << "\n";
			break;
		}
		for (int c : graph[x])
		{
			if (prec[c])
				continue;
			prec[c] = x;
			q.push({c, dist + 1});
		}
	}

	if (!prec[1])
	{
		std::cout << "IMPOSSIBLE\n";
		return 0;
	}

	int x = 1;
	while (x != -1)
	{
		std::cout << x << " ";
		x = prec[x];
	}
	return 0;
}
