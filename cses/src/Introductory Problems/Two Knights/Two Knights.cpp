#include <iostream>

int main()
{
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; ++i)
		std::cout << (1ll + (i - 1) * (i - 2) / 2) * (i - 1) * (i + 4) << '\n';
}
