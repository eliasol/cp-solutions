#include <iostream>

int main()
{
	int n;
	std::cin >> n;
	long long ans = 0;

	long long pow = 5;
	while (pow <= n)
	{
		ans += n / pow;
		pow *= 5;
	}

	std::cout << ans << std::endl;
}
