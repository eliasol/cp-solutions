#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <queue>
#include <tuple>

int main()
{
	int n, m;
	std::pair<int, int> a, b;
	std::cin >> n >> m;
	std::vector<std::vector<char>> grid(n, std::vector<char>(m, 0));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			char c;
			std::cin >> c;
			if (c == '#')
				grid[i][j] = 1;
			else if (c == 'A')
				a = {i, j};
			else if (c == 'B')
				b = {i, j};
		}
	}

	std::queue<std::tuple<int, int, char>> q;
	q.push({b.first, b.second, 0});

	while (!q.empty())
	{
		auto [i, j, c] = q.front();
		q.pop();
		if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j])
			continue;
		grid[i][j] = c;
		q.push({i, j + 1, 'L'});
		q.push({i, j - 1, 'R'});
		q.push({i + 1, j, 'U'});
		q.push({i - 1, j, 'D'});
	}

	if (grid[a.first][a.second] < 2)
	{
		std::cout << "NO\n";
		return 0;
	}

	std::string ans;

	while (a != b)
	{
		char next = grid[a.first][a.second];
		ans.push_back(next);
		switch (next)
		{
		case 'U':
			a = {a.first - 1, a.second};
			break;
		case 'D':
			a = {a.first + 1, a.second};
			break;
		case 'L':
			a = {a.first, a.second - 1};
			break;
		case 'R':
			a = {a.first, a.second + 1};
		}
	}

	std::cout << "YES\n" << ans.length() << "\n" << ans << "\n";

	return 0;
}
