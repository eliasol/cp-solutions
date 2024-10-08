#include <iostream>

int main()
{
	int t;
	std::cin >> t;
	while (t--)
	{
		int a, b;
		std::cin >> a >> b;
		std::cout << ((a + b) % 3 || b > 2 * a || a > 2 * b ? "NO" : "YES") << '\n';
	}
}
