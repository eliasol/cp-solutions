#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	int N, K;
	std::cin >> N >> K;
	std::vector<int> v(N);
	for (int& i : v)
		std::cin >> i;
	std::sort(v.begin(), v.end());
	std::vector<int>::iterator i = v.begin(), j = v.end();
	int ans = 0;
	while (i != j)
	{
		++ans;
		--j;
		if (i != j && *i + *j <= K)
			++i;
	}
	std::cout << ans << std::endl;
}
