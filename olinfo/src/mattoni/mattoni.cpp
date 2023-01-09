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

int n;
int fw[1000002];

void add(int x, int v)
{
	do
	{
		fw[x] += v;
		x += (x&-x);
	}
	while (x <= n);
}

int sum(int x)
{
	int ans = 0;
	do
	{
		ans += fw[x];
		x -= (x&-x);
	}
	while (x > 0);
	return ans;
}

int main()
{
	init_io();

	int m; cin >> n >> m;

	while (m--)
	{
		int l,r; cin >> l >> r;
		add(l,1);
		add(r+1,-1);
	}

	vector<int> vs(n);
	for (int i = 0; i < n; ++i) vs[i] = sum(i+1);
	sort(vs.begin(), vs.end());

	cout << vs[n/2] << "\n";

	return 0;
}
