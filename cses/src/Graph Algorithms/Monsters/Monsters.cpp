#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <string>
#include <algorithm>

int main()
{
	int n, m;
	std::cin >> n >> m;

	std::vector<std::vector<bool>> walls(n, std::vector<bool>(m, false));

	std::queue<std::array<int, 4>> q;
	std::array<int, 4> start;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			char c;
			std::cin >> c;
			if (c == '#')
				walls[i][j] = true;
			else if (c == 'M')
				q.push({i, j});
			else if (c == 'A')
				start = {i, j, 0, -1};
		}
	}

	std::vector<std::vector<int>> max_time(n, std::vector<int>(m, -1));

	while (!q.empty())
	{
		auto [i, j, dist, _] = q.front();
		q.pop();
		if (i < 0 || i >= n || j < 0 || j >= m || max_time[i][j] != -1 || walls[i][j])
			continue;
		max_time[i][j] = dist;
		q.push({i + 1, j, dist + 1});
		q.push({i - 1, j, dist + 1});
		q.push({i, j + 1, dist + 1});
		q.push({i, j - 1, dist + 1});
	}

	std::vector<std::vector<int>> prec(n, std::vector<int>(m, 0));
	q.push(start);

	std::array<int, 2> end = {-1, -1};

	while (!q.empty())
	{
		auto [i, j, dist, p] = q.front();
		q.pop();
		if (i < 0 || i >= n || j < 0 || j >= m || prec[i][j] || (max_time[i][j] != -1 && dist >= max_time[i][j]) || walls[i][j])
			continue;
		prec[i][j] = p;
		if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
		{
			end = {i, j};
			break;
		}
		q.push({i + 1, j, dist + 1, 1});
		q.push({i - 1, j, dist + 1, 3});
		q.push({i, j + 1, dist + 1, 4});
		q.push({i, j - 1, dist + 1, 2});
	}

	if (end[0] == -1)
	{
		std::cout << "NO\n";
		return 0;
	}

	std::string path;
	while (prec[end[0]][end[1]] != -1)
	{
		switch (prec[end[0]][end[1]])
		{
		case 1:
			path.push_back('D');
			end = {end[0] - 1, end[1]};
			break;
		case 2:
			path.push_back('L');
			end = {end[0], end[1] + 1};
			break;
		case 3:
			path.push_back('U');
			end = {end[0] + 1, end[1]};
			break;
		case 4:
			path.push_back('R');
			end = {end[0], end[1] - 1};
			break;
		}
	}

	std::reverse(path.begin(), path.end());
	std::cout << "YES\n" << path.length() << "\n" << path << "\n";
	return 0;
}
