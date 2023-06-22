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

	int n,k; cin >> n >> k;
	vector<int> c(n), u(n,0);
	for (int& i : c) cin >> i;

	long long ans = 0;

	while (k--)
	{
		int t,q; cin >> t >> q;
		if (u[t] + q > c[t])
			ans += c[t] - u[t], u[t] = 0;
		u[t] += q;
	}

	for (int i = 0; i < n; ++i)
		if (u[i] != 0)
			ans += c[i] - u[i];

	cout << ans << "\n";

	return 0;
}
