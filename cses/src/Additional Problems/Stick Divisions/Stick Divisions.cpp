#include <iostream>
#include <queue>

int main()
{
	int x, n;
	std::cin >> x >> n;

	std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		std::cin >> tmp;
		pq.push(tmp);
	}

	long long ans = 0;

	while (pq.size() > 1)
	{
		int x1 = pq.top();
		pq.pop();
		int x2 = pq.top();
		pq.pop();

		pq.push(x1 + x2);
		ans += x1 + x2;
	}

	std::cout << ans << std::endl;
}
