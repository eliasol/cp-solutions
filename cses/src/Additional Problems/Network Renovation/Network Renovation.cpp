#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <queue>

int main()
{
	int n;
	std::cin >> n;

	std::vector<std::vector<int>> tree(n + 1);

	for (int i = 0; i < n - 1; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	std::vector<int> leafs(n + 1, 0);
	std::vector<int> parents(n + 1, 0);

	std::function<void(int,int)> dp = [&tree = std::as_const(tree), &leafs, &dp, &parents] (int x, int p)
	{
		parents[x] = p;
		if (tree[x].size() == 1 && p != -1)
		{
			leafs[x] = 1;
			return;
		}

		leafs[x] = 0;

		for (int c : tree[x])
			if (c != p)
				dp(c, x), leafs[x] += leafs[c];
	};

	dp(1, -1);

	int centroidsus = 1;

	bool sussa = true;
	while (sussa)
	{
		std::pair<int, int> max = { leafs[1] - leafs[centroidsus], parents[centroidsus] };
		for (int c : tree[centroidsus])
			if (c != parents[centroidsus])
				max = std::max(max, { leafs[c], c });
		if (max.first > leafs[1] / 2)
			centroidsus = max.second;
		else
			sussa = false;
	}

	dp(centroidsus, -1);

	std::vector<std::vector<int>> tree_leafs(tree[centroidsus].size());

	std::function<void(int,std::vector<int>&)> dp2 = [&tree = std::as_const(tree), &parents = std::as_const(parents), &dp2] (int x, std::vector<int>& out)
	{
		if (tree[x].size() == 1 && parents[x] != -1)
			out.push_back(x);
		for (int c : tree[x])
			if (c != parents[x])
				dp2(c, out);
	};


	std::priority_queue<std::pair<int, int>> pq;

	for (int i = 0; i < tree[centroidsus].size(); ++i)
		dp2(tree[centroidsus][i], tree_leafs[i]), pq.push({ tree_leafs[i].size(), i });

	std::vector<int> ids(tree_leafs.size(), 0);

	std::vector<std::pair<int, int>> ans;

	while (!pq.empty())
	{
		auto [d, x] = pq.top();
		pq.pop();

		if (pq.empty())
		{
			ans.push_back({ tree_leafs[x][ids[x]++], centroidsus });
			continue;
		}

		auto [d1, x1] = pq.top();
		pq.pop();

		ans.push_back({ tree_leafs[x][ids[x]++], tree_leafs[x1][ids[x1]++] });

		if (d > 1)
			pq.push({ d - 1, x });
		if (d1 > 1)
			pq.push({ d1 - 1, x1 });
	}

	std::cout << ans.size() << '\n';
	for (auto [a, b] : ans)
		std::cout << a << ' ' << b << '\n';
}
