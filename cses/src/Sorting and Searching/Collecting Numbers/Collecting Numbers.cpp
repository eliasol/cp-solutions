#include <iostream>
#include <vector>

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> v(n);
	for (int& i : v)
		std::cin >> i;
	std::vector<int> pos(n + 1);
	for (int i = 0; i < n; ++i)
		pos[v[i]] = i;
	int ans = 1;
	for (int i = 2; i <= n; ++i)
		if (pos[i] < pos[i - 1])
			++ans;
	std::cout << ans << std::endl;
}
