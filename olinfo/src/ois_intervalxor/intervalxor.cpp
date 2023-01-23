#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n; cin >> n;

	while (n--)
	{
		int a; cin >> a;

		int xr = 0;

		int p = 1;
		for (int i = 0; i < 30; ++i, p*=2)
		{
			int conta = (a+1) / p;
			int conta2 = conta/2*p;

			int rim = (a+1) % p;
			if (conta%2) conta2 += rim;

			xr |= (conta2%2) << i;
		}

		int curr = 0;
		for (int i = 30; i >= 0; --i)
		{
			if ((xr >> i)&1) continue;
			if (curr + (1<<i) <= a) curr |= (1<<i);
		}

		cout << xr << " " << (xr^curr) << "\n";
	}
}
