#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solve()
{
	int n,m; cin >> n >> m;
	vector<vector<char>> m1(n, vector<char>(m)), m2(n, vector<char>(m));
	for (auto& i : m1)
		for (auto& j : i)
			cin >> j;
	for (auto& i : m2)
		for (auto& j : i)
			cin >> j;
	int x1 = m, y1 = n, x2 = 0, y2 = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (m1[i][j] == m2[i][j])
				continue;
			x1 = min(x1, j);
			y1 = min(y1, i);
			x2 = max(x2, j);
			y2 = max(y2, i);
		}
	}
	return max(0, (x2 - x1 + 1)) * (y2 - y1 + 1);
}

int main()
{
	int T; cin >> T;
	for (int t = 1; t <= T; ++t)
	{
		cout << "Case #" << t << ": " << solve() << "\n";
	}
}
