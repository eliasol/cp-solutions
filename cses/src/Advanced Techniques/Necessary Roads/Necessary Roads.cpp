#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;

	vector<vector<int>> g(n+1);

	for (int i = 0; i < m; ++i)
	{
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	vector<pair<int,int>> bridges;
	vector<int> back(n+1, 0), height(n+1, 0);

	auto dfs = [&](int x, int p, int h, auto dfs) -> void {
		if (back[x])
			return;
		back[x] = height[x] = h;
		for (int c : g[x])
		{
			if (c == p)
				continue;
			if (height[c])
				back[x] = min(back[x], height[c]);
			else
			{
				dfs(c, x, h + 1, dfs);
				if (back[c] > h)
					bridges.push_back({x, c});
				back[x] = min(back[x], back[c]);
			}
		}
	};

	dfs(1, -1, 1, dfs);

	cout << bridges.size() << "\n";
	for (auto& i : bridges)
		cout << i.first << " " << i.second << "\n";

	return 0;
}
