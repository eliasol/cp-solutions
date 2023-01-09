#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define init_io() cin.sync_with_stdio(0); cin.tie(0); cout.sync_with_stdio(0); cout.tie(0)

#define FILE_IO_LOCAL 1
#define FILE_IO_JUDGE 1

#if FILE_IO_LOCAL && !defined(EVAL) || FILE_IO_JUDGE && defined(EVAL)
ifstream fin("input.txt");
ofstream fout("output.txt");
#define cin fin
#define cout fout
#endif

const int INF = INT_MAX;

int main()
{
	init_io();

	int n,r,t,l; cin >> n >> r >> t >> l;

	vector<int> x(n);
	for (auto &i : x) cin >> i;

	if (x.back() < l) x.push_back(l);

	vector<vector<int>> dp(x.size(), vector<int>(r+1, INF));
	dp[0][r] = x[0];

	for (int i = 1; i < dp.size(); ++i)
	{
		for (int j = 0; j < dp[i].size(); ++j)
		{
			if (dp[i-1][j] != INF)
			{
				int nxtchange = ((dp[i-1][j] + t) / t) * t;
				if ((dp[i-1][j] / t) % 2 == 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + x[i] - x[i-1]);
				else dp[i][j] = min(dp[i][j], dp[i-1][j] + x[i] - x[i-1] + (nxtchange - dp[i-1][j]));
			}
			if (j == r) continue;
			if (dp[i-1][j+1] != INF)
			{
				if ((dp[i-1][j+1] / t) % 2 != 0) dp[i][j] = min(dp[i][j], dp[i-1][j+1] + x[i] - x[i-1]);
			}
		}
	}

	int ans = INF;

	for (int i = 0; i <= r; ++i) ans = min(ans, dp.back()[i]);

	cout << ans << "\n";

	return 0;
}
