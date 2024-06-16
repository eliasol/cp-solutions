#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <functional>

static constexpr int INF = 1e9 + 7;

int main()
{
	#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int N, K;
	std::cin >> N >> K;

	std::vector<std::vector<char>> g(N, std::vector<char>(N));

	std::pair<int, int> start;
	std::queue<std::pair<int, int>> q;

	std::vector<std::vector<int>> dist(N, std::vector<int>(N, INF));

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cin >> g[i][j];

			if (g[i][j] == 'M')
				start = { i, j };
			else if (g[i][j] == 'H')
			{
				dist[i][j] = 0;
				q.push({i, j});
			}
		}
	}

	while (!q.empty())
	{
		std::pair<int, int> x = q.front();
		q.pop();

		for (std::pair<int, int> offset : { std::pair<int,int>{ -1, 0 }, std::pair<int,int>{ 0, -1 }, std::pair<int,int>{ 1, 0 }, std::pair<int,int>{ 0, 1 } })
		{
			std::pair<int, int> coord = {x.first + offset.first, x.second + offset.second};
			if (coord.first < 0 || coord.first >= N || coord.second < 0 || coord.second >= N || g[coord.first][coord.second] == 'T' || g[coord.first][coord.second] == 'D' || dist[coord.first][coord.second] != INF)
				continue;
			dist[coord.first][coord.second] = dist[x.first][x.second] + 1;
			q.push({ coord.first, coord.second });
		}
	}

	int l = 0, r = (dist[start.first][start.second] == INF ? 1000000 : dist[start.first][start.second]);

	auto check = [&](int m) -> bool
	{
		bool flag = false;

		std::vector<std::vector<int>> distboh(N, std::vector<int>(N, INF));

		distboh[start.first][start.second] = m * K;
		q.push({start.first, start.second});

		while (!q.empty())
		{
			std::pair<int, int> x = q.front();
			q.pop();

			if (g[x.first][x.second] == 'D')
			{
				flag = true;
				continue;
			}

			for (std::pair<int, int> offset : { std::pair<int,int>{ -1, 0 }, std::pair<int,int>{ 0, -1 }, std::pair<int,int>{ 1, 0 }, std::pair<int,int>{ 0, 1 } })
			{
				std::pair<int, int> coord = {x.first + offset.first, x.second + offset.second};
				if (coord.first < 0 || coord.first >= N || coord.second < 0 || coord.second >= N || (g[coord.first][coord.second] != 'G' && g[coord.first][coord.second] != 'D') || distboh[coord.first][coord.second] != INF || (distboh[x.first][x.second] + 1) / K >= dist[coord.first][coord.second])
					continue;
				distboh[coord.first][coord.second] = distboh[x.first][x.second] + 1;
				q.push({ coord.first, coord.second });
			}
		}

		return flag;
	};

	while (r - l > 1)
	{
		int m = (l + r) / 2;

		if (check(m))
			l = m;
		else
			r = m;
	}

	std::cout << (check(l) ? l : -1) << std::endl;
}
