#include <iostream>
#include <vector>
#include <unordered_set>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::unordered_set<int> seen;
	std::vector<int> v(n);
	for (int& i : v)
		std::cin >> i;
	for (int i = n - 1; i >= 0; --i)
	{
		seen.insert(v[i]);
		v[i] = seen.size();
	}
	while (m--)
	{
		int b;
		std::cin >> b;
		std::cout << v[b - 1] << "\n";
	}
	return 0;
}
