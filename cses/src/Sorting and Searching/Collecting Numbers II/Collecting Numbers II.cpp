#include <iostream>
#include <vector>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::vector<int> v(n);
	for (int& i : v)
		std::cin >> i;
	v.insert(v.begin(), 0);
	std::vector<int> pos(n + 2);
	pos[0] = 0;
	pos[n + 1] = n + 1;
	for (int i = 1; i <= n; ++i)
		pos[v[i]] = i;
	int ans = 1;
	for (int i = 2; i <= n; ++i)
		if (pos[i] < pos[i - 1])
			++ans;
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		if (a > b)
			std::swap(a, b);
		if (pos[v[a] - 1] >= a && pos[v[a] - 1] <= b)
			--ans;
		if (pos[v[a] + 1] >= a && pos[v[a] + 1] <= b)
			++ans;
		if (pos[v[b] - 1] >= a && pos[v[b] - 1] <= b)
			++ans;
		if (pos[v[b] + 1] >= a && pos[v[b] + 1] <= b)
			--ans;
		if (std::abs(v[a] - v[b]) == 1)
		{
			if (v[a] < v[b])
				--ans;
			else
				++ans;
		}
		std::swap(pos[v[a]], pos[v[b]]);
		std::swap(v[a], v[b]);
		std::cout << ans << "\n";
	}
}
