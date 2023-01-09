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

	int n,c; cin >> n >> c;
	vector<int> v(n);
	for (int& i : v) cin >> i;

	int best = n;
	int count = 0;
	vector<int> found(c,0);

	int l = 0, r = 0;

	while (r < n)
	{
		while (r < n && count < c)
		{
			if (!found[v[r]]) ++count;
			++found[v[r++]];
		}
		if (count < c) break;
		while (l < r && found[v[l]] > 1) --found[v[l++]];
		best = min(best, r-l);
		--found[v[l++]];
		--count;
	}

	cout << best << "\n";

	return 0;
}
