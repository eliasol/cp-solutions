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
	vector<int> p(n);
	for (auto &i : p) cin >> i;

	int best = 1e9;
	for (auto &i : p) best = min(best, max(abs(i-p[0]), abs(i-p[n-1])));

	cout << best << "\n";

	return 0;
}
