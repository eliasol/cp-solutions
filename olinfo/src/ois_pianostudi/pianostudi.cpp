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

int main()
{
	init_io();

	int n; cin >> n;

	struct corso { int da,a,crediti; };

	vector<corso> corsi(n);
	for (auto &i : corsi) cin >> i.da >> i.a >> i.crediti;

	sort(corsi.begin(),corsi.end(), [](const corso& a, const corso& b) -> bool { return a.a < b.a; });

	vector<int> best(n), dp(n);
	dp[0] = best[0] = corsi[0].crediti;

	for (int i = 1; i < n; ++i)
	{
		int l = 0, r = i-1;
		while (l < r)
		{
			int m = (l+r+1)/2;
			if (corsi[m].a < corsi[i].da) l = m;
			else r = m-1;
		}
		if (corsi[l].a >= corsi[i].da) dp[i] = corsi[i].crediti;
		else dp[i] = best[l] + corsi[i].crediti;
		best[i] = max(best[i-1],dp[i]);
	}

	cout << best[n-1] << "\n";

	return 0;
}
