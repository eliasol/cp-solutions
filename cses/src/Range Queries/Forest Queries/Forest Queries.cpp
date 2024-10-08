#include <iostream>
#include <vector>
#include <string>

int main()
{
	int n, q;
	std::cin >> n >> q;

	std::vector<std::vector<int>> v(n + 1, std::vector<int>(n + 1, 0));
	for (int i = 0; i < n; ++i)
	{
		std::string s;
		std::cin >> s;
		for (int j = 0; j < n; ++j)
			v[i + 1][j + 1] = v[i + 1][j] + v[i][j + 1] - v[i][j] + (s[j] == '*');
	}

	while (q--)
	{
		int x1, y1, x2, y2;
		std::cin >> x1 >> y1 >> x2 >> y2;
		std::cout << v[x2][y2] - v[x2][y1 - 1] - v[x1 - 1][y2] + v[x1 - 1][y1 - 1] << '\n';
	}
}
