#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <stack>

int main()
{
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int>> events(2 * n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> events[2 * i].first >> events[2 * i + 1].first;
		events[2 * i + 1].first *= -1;
		events[2 * i].second = events[2 * i + 1].second = i;
	}
	std::sort(events.begin(), events.end(), [](std::pair<int, int> a, std::pair<int, int> b)
	{
		if (std::abs(a.first) == std::abs(b.first))
			return a.first > b.first;
		return std::abs(a.first) < std::abs(b.first);
	});
	std::stack<int> s;
	for (int i = n; i > 0; --i)
		s.push(i);
	std::vector<int> ans(n, -1);
	for (std::pair<int, int> event : events)
	{
		if (event.first > 0)
			ans[event.second] = s.top(), s.pop();
		else
			s.push(ans[event.second]);
	}
	std::cout << *std::max_element(ans.begin(), ans.end()) << "\n";
	for (int i : ans)
		std::cout << i << " ";
}
