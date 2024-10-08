#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>

int main()
{
	int n, q;
	std::cin >> n >> q;

	std::vector<int> s(n);

	for (int& i : s)
		std::cin >> i;

	std::vector<int> ids(s);
	std::vector<std::tuple<char, int, int>> queries(q);

	ids.push_back(0);

	for (auto &[t, a, b] : queries)
	{
		std::cin >> t >> a >> b;
		if (t == '!')
			ids.push_back(b);
	}

	std::sort(ids.begin(), ids.end());
	ids.resize(std::unique(ids.begin(), ids.end()) - ids.begin());

	std::vector<int> fw(ids.size() + 1);

	std::function<void(int,int)> fw_add = [&fw] (int x, int v)
	{
		++x;
		for (; x < fw.size(); x += x&-x)
			fw[x] += v;
	};

	std::function<int(int)> fw_sum = [&fw] (int x)
	{
		int sum = 0;
		++x;
		for (; x > 0; x -= x&-x)
			sum += fw[x];
		return sum;
	};

	for (int i : s)
		fw_add(std::lower_bound(ids.begin(), ids.end(), i) - ids.begin(), 1);

	for (auto [t, a, b] : queries)
	{
		if (t == '?')
			std::cout << fw_sum(std::prev(std::upper_bound(ids.begin(), ids.end(), b)) - ids.begin()) - fw_sum(std::prev(std::lower_bound(ids.begin(), ids.end(), a)) - ids.begin()) << '\n';
		else
			fw_add(std::lower_bound(ids.begin(), ids.end(), s[a - 1]) - ids.begin(), -1),
			fw_add(std::lower_bound(ids.begin(), ids.end(), b) - ids.begin(), 1),
			s[a - 1] = b;
	}
}
