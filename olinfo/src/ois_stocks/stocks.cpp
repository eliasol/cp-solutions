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
	vector<int> v(n),s(n);
	for (auto& i : v) cin >> i;
	for (auto& i : s) cin >> i;

	int i = -1, best = 0, act = 0;

	while (++i < n)
	{
		if (!s[i]) act = 0;
		else if (i == 0 || v[i-1] <= v[i]) act += v[i];
		else act = v[i];
		best = max(best,act);
	}

	cout << best << "\n";

	return 0;
}
