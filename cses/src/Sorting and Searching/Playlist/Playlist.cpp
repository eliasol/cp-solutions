#include <iostream>
#include <vector>
#include <bitset>

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> v(n);
	for (int& i : v)
		std::cin >> i;
	std::bitset<1 << 30> check;
	int l = 0, ans = 0;
	for (int r = 0; r < n; ++r)
	{
		while (check[v[r]])
			check[v[l++]] = 0;
		check[v[r]] = 1;
		ans = std::max(ans, r - l + 1);
	}
	std::cout << ans << std::endl;
}
