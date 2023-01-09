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

struct piatto
{
	int inizio, durata, valore, fine;

	bool operator<(const piatto& a) const {return fine < a.fine;}
};

int main()
{
	init_io();

	int n; cin >> n;

	vector<piatto> piatti(n);
	vector<int> dp(n);
	vector<int> ma(n, 0);

	for (auto &p : piatti)
	{
		cin >> p.inizio >> p.valore >> p.durata;
		p.fine = p.inizio + p.durata;
	}

	sort(piatti.begin(), piatti.end());

	for (int i = 0; i < n; ++i) dp[i] = piatti[i].valore;

	ma[0] = dp[0];
	for (int i = 1; i < n; ++i)
	{        
		int l = 0, r = i-1;

		while (l < r)
		{
			int m = (l+r+1)/2;
			if (piatti[m].fine <= piatti[i].inizio) l = m;
			else r = m-1;
		}

		if (l == r && piatti[l].fine <= piatti[i].inizio)
		{
			dp[i] = max(dp[i], ma[l] + piatti[i].valore);
		}
		ma[i] = max(ma[i-1], dp[i]);
	}

	cout << ma[n-1] << "\n";

	return 0;
}
