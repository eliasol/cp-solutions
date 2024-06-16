#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>

int main()
{
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int>> v(n);
	for (int i = 0; i < n; ++i)
		std::cin >> v[i].first, v[i].second = i;
	std::sort(v.rbegin(), v.rend());
	std::set<int> s;
	for (int i = 0; i < n; ++i)
	{
		std::set<int>::iterator it = s.lower_bound(v[i].second);
		if (it != s.begin())
			s.erase(std::prev(it));
		s.insert(v[i].second);
	}
	std::cout << s.size() << std::endl;
}
