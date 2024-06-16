#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> v(n);

	for (int& i : v)
		std::cin >> i;

	std::nth_element(v.begin(), v.begin() + n / 2, v.end());
	std::transform(v.begin(), v.end(), v.begin(), [x = v[n / 2]] (int i) { return std::abs(x - i); });
	std::cout << std::accumulate(v.begin(), v.end(), 0LL) << std::endl;
}
