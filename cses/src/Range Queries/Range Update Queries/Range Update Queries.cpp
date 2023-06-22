#include <iostream>
#include <vector>

std::vector<long long> ft;

void add(int x, int v)
{
	while (x < (int) ft.size())
	{
		ft[x] += v;
		x += x&-x;
	}
}

long long get(int x)
{
	long long sum = 0;
	while (x > 0)
	{
		sum += ft[x];
		x -= x&-x;
	}
	return sum;
}

int main()
{
	int n, q;
	std::cin >> n >> q;
	ft.resize(n + 1);
	ft[0] = 0;

	int last = 0;
	for (int i = 1; i <= n; ++i)
	{
		int x;
		std::cin >> x;
		ft[i] = x - last + ft[i - 1];
		last = x;
	}

	for (int i = n; i > 0; --i)
		ft[i] = ft[i] - ft[i - (i&-i)];

	while (q--)
	{
		int t;
		std::cin >> t;
		if (t == 1)
		{
			int a, b, u;
			std::cin >> a >> b >> u;
			add(a, u);
			add(b + 1, -u);
		}
		else
		{
			int k;
			std::cin >> k;
			std::cout << get(k) << "\n";
		}
	}
	return 0;
}
