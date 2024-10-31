#include <iostream>
#include <vector>

constexpr int MOD = 1e9 + 7;

class dsu
{
private:
	int components;
	std::vector<int> data;

public:
	dsu(int n) : components(n), data(n, -1) {}

	int find(int x)
	{
		if (data[x] < 0)
			return x;
		return data[x] = find(data[x]);
	}

	void merge(int a, int b)
	{
		a = find(a);
		b = find(b);

		if (a == b)
			return;
		--components;
		data[a] = b;
	}

	int count() { return components; }
};

int main()
{
	int n;
	std::cin >> n;

	std::vector<int> parent(n + 1);
	std::vector<int> open(n + 1), close(n + 1);

	{
		std::vector<std::vector<int>> g(n + 1);
		for (int i = 0; i < n - 1; ++i)
		{
			int a, b;
			std::cin >> a >> b;
			g[a].push_back(b);
			g[b].push_back(a);
		}

		int time = 0;

		auto dfs = [&] (int x, int p, auto dfs) -> void
		{
			parent[x] = p;
			open[x] = time++;
			for (int c : g[x])
				if (c != p)
					dfs(c, x, dfs);
			close[x] = time++;
		};

		dfs(1, -1, dfs);
	}

	dsu d(n + 1);

	auto is_ancestor = [&] (int x, int c) -> bool { return open[c] >= open[x] && close[c] <= close[x]; };

	int q;
	std::cin >> q;

	while (q--)
	{
		int a, b;
		std::cin >> a >> b;

		int lasta = a, lastb = b;

		while (!is_ancestor(a, b))
			d.merge(lasta, a), lasta = a, a = parent[d.find(a)];
		while (!is_ancestor(b, a))
			d.merge(lastb, b), lastb = b, b = parent[d.find(b)];

		if (a != lasta && b != lastb)
			d.merge(lasta, lastb);
	}

	int p = d.count() - 2;
	int ans = 1;

	while (p--)
		ans = (2 * ans) % MOD;
	std::cout << ans << std::endl;
}
