#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define init_io() cin.sync_with_stdio(0); cin.tie(0); cout.sync_with_stdio(0); cout.tie(0)

#define FILE_IO_LOCAL 0
#define FILE_IO_JUDGE 0

#if FILE_IO_LOCAL && !defined(EVAL) || FILE_IO_JUDGE && defined(EVAL)
ifstream fin("input.txt");
ofstream fout("output.txt");
#define cin fin
#define cout fout
#endif

int main()
{
	init_io();

	int n; cin >> n;

	int best_rect[n+1];
	for (int i = 1; i <= n; ++i) best_rect[i] = INT_MAX;
	for (int i = 1; i*i <= n; ++i)
		for (int j = i; j <= n; j+=i)
			best_rect[j] = min(best_rect[j], 2*(i+j/i));

	int dp[2][n+1];
	int *dp1 = dp[0], *dp2 = dp[1];

	dp1[0] = 0;
	for (int i = 1; i <= n; ++i) dp1[i] = INT_MAX;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j < i; ++j) dp2[j] = dp1[j];
		for (int j = i; j <= n; ++j) dp2[j] = min(dp1[j], dp2[j-i] + best_rect[i]);
		swap(dp1,dp2);
	}

	cout << dp1[n] << "\n";

	return 0;
}
