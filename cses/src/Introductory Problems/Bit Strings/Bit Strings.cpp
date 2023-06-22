#include <iostream>

constexpr int mod = 1e9+7;

int main()
{
	long long n, base = 2, r = 1;
	std::cin >> n;
	while (n > 0)
	{
		if (n & 1)
			r *= base, r %= mod;
		base *= base;
		base %= mod;
		n /= 2;
	}
	std::cout << r << "\n";
	return 0;
}
