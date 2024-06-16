#include <iostream>
#include <vector>
#include <deque>

int main()
{
	int n, a, b;
	std::cin >> n >> a >> b;
	std::vector<long long> prefix(n);
	for (long long& i : prefix)
		std::cin >> i;
	prefix.insert(prefix.begin(), 0);
	for (int i = 1; i <= n; ++i)
		prefix[i] = prefix[i] + prefix[i - 1];
	std::deque<int> maxqueue;
	long long ans = -1e18;
	for (int i = a; i <= n; ++i)
	{
		while (!maxqueue.empty() && prefix[maxqueue.back()] >= prefix[i - a])
			maxqueue.pop_back();
		maxqueue.push_back(i - a);
		while (!maxqueue.empty() && i - maxqueue.front() > b)
			maxqueue.pop_front();
		ans = std::max(ans, prefix[i] - prefix[maxqueue.front()]);
	}
	std::cout << ans << std::endl;
}
