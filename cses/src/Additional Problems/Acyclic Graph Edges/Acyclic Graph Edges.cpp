#include <iostream>
#include <algorithm>

int main()
{
	int n, m;
	std::cin >> n >> m;

	while (m--)
	{
		int a, b;
		std::cin >> a >> b;
		if (b < a)
			std::swap(a, b);
		std::cout << a << " " << b << "\n";
	}
}
