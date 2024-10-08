#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

int main()
{
	std::string s;
	std::cin >> s;
	std::sort(s.begin(), s.end());
	std::queue<std::string> ans;

	ans.push(s);
	while (std::next_permutation(s.begin(), s.end()))
		ans.push(s);

	std::cout << ans.size() << '\n';
	while (!ans.empty())
		std::cout << ans.front() << '\n', ans.pop();
}
