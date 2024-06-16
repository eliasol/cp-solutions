#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

class segment_tree
{
private:
	size_t tree_size;
	std::vector<long long> data, lz;

	void push(size_t x, int l, int r)
	{
		int m = (l + r) / 2;
		data[2 * x] += lz[x];
		data[2 * x + 1] += lz[x];
		if (2 * x < tree_size)
			lz[2 * x] += lz[x], lz[2 * x + 1] += lz[x];
		lz[x] = 0;
	}

	long long max(int a, int b, size_t x, int l, int r)
	{
		if (r <= a || l >= b)
			return std::numeric_limits<long long>::min();
		if (l >= a && r <= b)
			return data[x];
		push(x, l, r);
		int m = (l + r) / 2;
		return std::max(max(a, b, 2 * x, l, m), max(a, b, 2 * x + 1, m, r));
	}

	void add(int a, int b, long long v, size_t x, int l, int r)
	{
		if (r <= a || l >= b)
			return;
		if (l >= a && r <= b)
		{
			if (x < tree_size)
				lz[x] += v;
			data[x] += v;
			return;
		}
		push(x, l, r);
		int m = (l + r) / 2;
		add(a, b, v, 2 * x, l, m);
		add(a, b, v, 2 * x + 1, m, r);
		data[x] = std::max(data[2 * x], data[2 * x + 1]);
	}

public:
	template<typename It>
	segment_tree(It begin, It end) : tree_size(1 << (size_t) std::ceil(std::log2(end - begin))), data(2 * tree_size, std::numeric_limits<long long>::min()), lz(tree_size, 0)
	{
		std::copy(begin, end, data.begin() + tree_size);
		for (size_t i = tree_size - 1; i > 0; --i)
			data[i] = std::max(data[2 * i], data[2 * i + 1]);
	}

	long long max(int a, int b) { return max(a, b, 1, 0, tree_size); }
	void add(int a, int b, long long v) { add(a, b, v, 1, 0, tree_size); }
};

int main()
{
	size_t n, q;
	std::cin >> n >> q;

	std::vector<int> v(n);
	std::vector<long long> pref(n + 1);

	for (int& i : v)
		std::cin >> i;
	pref[0] = 0;
	for (size_t i = 1; i <= n; ++i)
		pref[i] = pref[i - 1] + v[i - 1];

	segment_tree tree(pref.begin(), pref.end());

	while (q--)
	{
		int t, a, b;
		std::cin >> t >> a >> b;

		if (t == 1)
		{
			tree.add(a, n + 1, b - v[a - 1]);
			v[a - 1] = b;
		}
		else
		{
			std::cout << tree.max(a - 1, b + 1) - tree.max(a - 1, a) << "\n";
		}
	}
}
