#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> v(n);
	for (int& i : v)
		std::cin >> i;
	std::sort(v.begin(), v.end());
	long long ans = 1;
	for (int i = 0; i < n; ++i)
	{
		if (v[i] > ans)
			break;
		ans += v[i];
	}
	std::cout << ans << std::endl;
}
