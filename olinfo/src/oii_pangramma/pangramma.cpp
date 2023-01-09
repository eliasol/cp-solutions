#include <vector>
#include <iostream>

using namespace std;

constexpr int MOD = 46337;

long long memo[10000000];

long long fastexp(long long a, long long b)
{
	if (memo[a]) return memo[a];
	if (b == 0) return 1;
	long long tmp = fastexp(a,b/2);
	tmp = (tmp*tmp) % MOD;
	if (b%2) tmp = (tmp*a)%MOD;
	return memo[a] = tmp;
}

long long inverse(long long a)
{
	return fastexp(a, MOD-2);
}

int conta(int N, int K, vector<int>& V)
{
	long long count = 0, ans = 0;
	long long prod = 1;
	int len = N;
	vector<int> occurrencies(K,0);
	int l = 0, r = 0;

	while (r < N)
	{
		while (r < N && count < K)
		{
			if (!occurrencies[V[r]]) ++count;
			else prod = (prod * inverse(occurrencies[V[r]])) % MOD;
			++occurrencies[V[r]];
			prod = (prod * occurrencies[V[r]]) % MOD;
			++r;
		}
		if (count < K) break;

		while (l < r && occurrencies[V[l]] > 1)
		{
			prod = (prod * inverse(occurrencies[V[l]])) % MOD;
			--occurrencies[V[l]];
			prod = (prod * occurrencies[V[l]]) % MOD;
			++l;
		}

		if (r-l < len) len = r-l, ans = prod;
		else if (r-l == len) ans = (ans + prod) % MOD;

		prod = (prod * inverse(occurrencies[V[l]])) % MOD;
		--occurrencies[V[l]];
		++l;

		--count;
	}

	return ans;
}
