#include <iostream>
#include <vector>
#include <functional>

static constexpr int SIDE = 8;

int main()
{
	std::vector<std::vector<bool>> res(SIDE, std::vector<bool>(SIDE, false));
	for (int i = 0; i < SIDE; ++i)
	{
		for (int j = 0; j < SIDE; ++j)
		{
			char c;
			std::cin >> c;
			if (c == '*')
				res[i][j] = true;
		}
	}

	std::vector<bool> col(SIDE, false);
	std::vector<bool> diags(2 * SIDE, false);
	std::vector<bool> diagd(2 * SIDE, false);

	std::function<int(int)> brute = [&] (int x) -> int
	{
		if (x == SIDE)
			return 1;
		int ans = 0;
		for (int y = 0; y < SIDE; ++y)
		{
			if (res[x][y] || col[y] || diags[x + y] || diagd[SIDE + y - x])
				continue;
			col[y] = true;
			diags[x + y] = true;
			diagd[SIDE + y - x] = true;

			ans += brute(x + 1);

			col[y] = false;
			diags[x + y] = false;
			diagd[SIDE + y - x] = false;
		}
		return ans;
	};

	std::cout << brute(0) << std::endl;
}
