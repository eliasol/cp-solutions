#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pii pair<int,int>
#define init_io() cin.sync_with_stdio(0); cin.tie(0); cout.sync_with_stdio(0); cout.tie(0)

#define FILE_IO_LOCAL 1
#define FILE_IO_JUDGE 1

#if FILE_IO_LOCAL && !defined(EVAL) || FILE_IO_JUDGE && defined(EVAL)
ifstream fin("input.txt");
ofstream fout("output.txt");
#define cin fin
#define cout fout
#endif

inline int dist(pii& p1, pii& p2)
{
	return (p1.first-p2.first)*(p1.first-p2.first) + (p1.second-p2.second)*(p1.second-p2.second);
}

int main()
{
	init_io();

	int n; cin >> n;
	vector<pii> t;

	char c;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			cin >> c;
			if (c == 'T') t.push_back({i,j});
		}

	n = t.size();
	vector<int> best(n, INT_MAX);
	best[0] = 0;

	int k = n;
	ll ans = 0;

	while (k--)
	{
		int mn = INT_MAX, mni;
		for (int i = 0; i < n; ++i)
		{
			if (best[i] == -1) continue;
			if (best[i] < mn)
			{
				mn = best[i];
				mni = i;
			}
		}
		ans += mn;
		best[mni] = -1;
		for (int i = 0; i < n; ++i)
		{
			if (best[i] == -1) continue;
			best[i] = min(best[i], dist(t[i],t[mni]));
		}
	}

	cout << ans << "\n";

	return 0;
}
