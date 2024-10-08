#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

int main()
{
	int n, m, k;
	std::cin >> n >> m >> k;

	std::set<std::pair<int, int>> sussone;
	std::vector<std::pair<int, int>> edges, remove;

	for (int i = 0; i < m; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		if (a > b)
			std::swap(a, b);
		edges.push_back({ a, b });
	}

	for (int i = 0; i < k; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		if (a > b)
			std::swap(a, b);
		sussone.insert({ a, b });
		remove.push_back({ a, b });
	}

	std::reverse(remove.begin(), remove.end());

	int component = n;
	std::vector<int> dsu(n + 1, -1);

	auto group = [&dsu] (int x, auto group) -> int
	{
		if (dsu[x] < 0)
			return x;
		return dsu[x] = group(dsu[x], group);
	};

	auto merge = [&dsu, &group, &component] (int a, int b)
	{
		a = group(a, group);
		b = group(b, group);
		if (a == b)
			return;
		if (-dsu[a] > -dsu[b])
			dsu[b] = a;
		else if (-dsu[b] > -dsu[a])
			dsu[a] = b;
		else
			dsu[a] = b, --dsu[b];
		--component;
	};

	std::vector<int> ans;
	for (int i = 0; i < m; ++i)
		if (!sussone.count(edges[i]))
			merge(edges[i].first, edges[i].second);

	for (auto i : remove)
	{
		ans.push_back(component);
		merge(i.first, i.second);
	}

	std::reverse(ans.begin(), ans.end());

	for (int i : ans)
		std::cout << i << " ";
	std::cout << std::endl;
}
