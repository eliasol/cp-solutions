#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define init_io() cin.sync_with_stdio(0); cin.tie(0); cout.sync_with_stdio(0); cout.tie(0)

#define FILE_IO_LOCAL 0
#define FILE_IO_JUDGE 1

#if FILE_IO_LOCAL && !defined(EVAL) || FILE_IO_JUDGE && defined(EVAL)
ifstream fin("input.txt");
ofstream fout("output.txt");
#define cin fin
#define cout fout
#endif

vector<int> jmps;

int play(int x)
{
	int pos = 0, cnt = 0;
	while (pos < jmps.size())
	{
		++cnt;
		pos += x;
		while (pos < jmps.size() && jmps[pos]) pos += jmps[pos];
	}
	return cnt;
}

int main()
{
	init_io();

	int n; cin >> n;
	jmps.resize(n);

	for (auto &i : jmps) cin >> i;

	for (int i = 1; i <= 6; ++i) cout << play(i) << " ";
	cout << "\n";

	return 0;
}
