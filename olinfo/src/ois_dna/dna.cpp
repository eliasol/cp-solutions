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

	int n,m; cin >> n >> m;
	vector<bitset<100>> s(n);
	for (auto &i : s)
	{
		string st; cin >> st;
		i = bitset<100>(st);
	}

	int ans = 0;

	vector<int> best(n,m);
	int k = n;
	while (k--)
	{
		int mn = m+1, mni;
		for (int i = 0; i < n; ++i)
		{
			if (best[i] == -1) continue;
			if (best[i] < mn)
			{
				mn = best[i];
				mni = i;
			}
		}
		ans += best[mni];
		best[mni] = -1;
		for (int i = 0; i < n; ++i)
		{
			if (best[i] == -1) continue;
			best[i] = min(best[i], (int) (s[i]^s[mni]).count());
		}
	}

	cout << ans << "\n";

	return 0;
}
