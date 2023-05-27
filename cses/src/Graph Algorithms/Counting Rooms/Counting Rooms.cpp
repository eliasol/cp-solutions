#include <iostream>
#include <vector>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<bool>> grid(n, std::vector<bool>(m, 0));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			char c;
			std::cin >> c;
			if (c == '#')
				grid[i][j] = true;
		}
	}

	auto dfs = [&](int i, int j, auto dfs) -> void {
		if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j])
			return;
		grid[i][j] = true;
		dfs(i, j + 1, dfs);
		dfs(i, j - 1, dfs);
		dfs(i + 1, j, dfs);
		dfs(i - 1, j, dfs);
	};

	int ans = 0;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (!grid[i][j])
				dfs(i, j, dfs), ++ans;

	std::cout << ans << std::endl;

	return 0;
}
