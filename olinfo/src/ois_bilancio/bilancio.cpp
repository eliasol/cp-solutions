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

	vector<int> str(n+1);
	vector<int[10]> prefix(n+1);

	for (int i = 0; i < 10; ++i) prefix[0][i] = 0;
	for (int i = 1; i <= n; ++i)
	{
		int x; cin >> x;
		str[i] = x;
		for (int j = 0; j < 10; ++j) prefix[i][j] = prefix[i-1][j];
		++prefix[i][x];
	}

	for (int i = 1; i <= n && k < n-i+1; ++i)
	{
		int j;
		for (j = 0; j < 10; ++j)
			if (prefix[i+k][j]-prefix[i-1][j] > 0) break;
		while (str[i] != j)
		{
			++i;
			--k;
		}
		cout << j << " ";
	}

	return 0;
}
