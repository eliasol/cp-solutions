#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
	int x, n;
	std::cin >> x >> n;
	std::vector<int> v(n);
	for (int i = 0; i < n; ++i)
		std::cin >> v[n - i - 1];
	std::set<int> s(v.begin(), v.end());
	s.insert(0);
	s.insert(x);
	int curr = 0;
	for (std::set<int>::iterator it = std::next(s.begin()); it != s.end(); ++it)
		curr = std::max(*it - *std::prev(it), curr);
	std::vector<int> ans;
	for (int i : v)
	{
		ans.push_back(curr);
		std::set<int>::iterator it = s.find(i);
		curr = std::max(curr, *std::next(it) - *std::prev(it));
		s.erase(it);
	}
	while (!ans.empty())
		std::cout << ans.back() << " ", ans.pop_back();
	std::cout << std::endl;
}
