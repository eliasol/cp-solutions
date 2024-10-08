#include <vector>
#include <algorithm>

static constexpr int MOD = 1e9 + 7;

template<typename T, typename TM>
static constexpr TM posmod(T n, TM m) { return ((n % m) + m) % m; }

std::vector<int> execute(int N, int K, int D, std::vector<int> A)
{
	if (K == 1)
		return A;
	std::vector<int> tmp = execute(N, K / 2, D, A);
	std::vector<int> ans(N);
	for (int i = 0; i < N; ++i)
		ans[i] = (tmp[i] * (long long) tmp[posmod(i - D * (long long) (K / 2), N)]) % MOD;
	if (K & 1)
		for (int i = 0; i < N; ++i)
			ans[i] = (ans[i] * (long long) A[posmod(i - D * (long long) (K - 1), N)]) % MOD;
	return ans;
}
