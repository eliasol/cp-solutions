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

	int n,m,k; cin >> n >> m >> k;
	vector<int> l(n);
	for (auto& i : l) cin >> i;

	int conta = 0, ris = 0;
	for (int i = 0; i < m; ++i) conta += l[i];

	for (int i = m-1; conta < k; --i)
	{
		if (l[i]) continue;
		l[i] = 1;
		++conta;
		++ris;
	}

	for (int i = m; i < n; ++i)
	{
		conta += l[i] - l[i-m];
		if (conta < k)
		{
			l[i] = 1;
			++ris;
			++conta;
		}
	}

	cout << ris << "\n";

	return 0;
}
