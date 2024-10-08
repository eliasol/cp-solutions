#include <iostream>
#include <array>
#include <stack>
#include <functional>

int main()
{
	int n;
	std::cin >> n;

	std::cout << (1 << n) - 1 << '\n';

	std::array<std::stack<int>, 3> v;

	v[0].push(n + 1);
	v[1].push(n + 1);
	v[2].push(n + 1);

	for (int i = n; i > 0; --i)
		v[0].push(i);

	const std::array<int, 3> real = (n & 1) ? std::array<int, 3>{ 1, 3, 2 } : std::array<int, 3>{ 1, 2, 3 };

	std::function<void(int,int)> move = [&real, &v] (int a, int b)
	{
		if (v[a].top() < v[b].top())
			v[b].push(v[a].top()), v[a].pop(), std::cout << real[a] << ' ' << real[b] << '\n';
		else
			v[a].push(v[b].top()), v[b].pop(), std::cout << real[b] << ' ' << real[a] << '\n';
	};

	for (int i = 0; i < (1 << n) - 1; ++i)
	{
		switch (i % 3)
		{
		case 0:
			move(0, 1);
			break;
		case 1:
			move(0, 2);
			break;
		default:
			move(1, 2);
		}
	}
}
