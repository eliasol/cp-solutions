#include <iostream>
#include <array>

static constexpr std::array<long long, 19> pows = {
	1LL,
	10LL,
	100LL,
	1000LL,
	10000LL,
	100000LL,
	1000000LL,
	10000000LL,
	100000000LL,
	1000000000LL,
	10000000000LL,
	100000000000LL,
	1000000000000LL,
	10000000000000LL,
	100000000000000LL,
	1000000000000000LL,
	10000000000000000LL,
	100000000000000000LL,
	1000000000000000000LL
};

int main()
{
	int q;
	std::cin >> q;

	while (q--)
	{
		long long k;
		std::cin >> k;

		long long curr = 0;
		int i = 1;

		for (; curr + (pows[i] - pows[i - 1]) * i < k; ++i)
			curr += (pows[i] - pows[i - 1]) * i;

		long long x = pows[i - 1] + (k - curr - 1) / i;

		int sus = (k - curr - 1) % i;
		int want = i - sus - 1;

		int ans = (x / pows[want]) % 10;
		std::cout << ans << '\n';
	}
}
