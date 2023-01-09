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

struct torneo
{
	int inizio = 0, fine = 0, prezzo = 0, premio = 0;

	bool operator<(const torneo& t) const {return fine < t.fine;}
};

int main()
{
	init_io();

	int n,m; cin >> n >> m;

	vector<torneo> tornei(n);

	for (int i = 0; i < n; ++i)
	{
		int giorno, inizio, fine, prezzo, premio; cin >> giorno >> inizio >> fine >> prezzo >> premio;
		torneo &t = tornei[i];
		t.inizio = 1001*giorno+inizio;
		t.fine = 1001*giorno+fine;
		t.prezzo = prezzo;
		t.premio = premio;
	}

	sort(tornei.begin(), tornei.end());

	vector<int> dp(n);
	vector<int> ma(n,0);

	for (int i = 0; i < n; ++i)
	{
		dp[i] = tornei[i].prezzo > m ? 0 : (m-tornei[i].prezzo+tornei[i].premio);
	}

	ma[0] = dp[0];

	for (int i = 1; i < n; ++i)
	{
		int l = 0, r = i-1;

		while (l < r)
		{
			int m = (l+r+1)/2;
			if (tornei[m].fine <= tornei[i].inizio) l = m;
			else r = m-1;
		}

		if (l == r && tornei[l].fine <= tornei[i].inizio && ma[l] >= tornei[i].prezzo) 
		{
			dp[i] = max(dp[i], ma[l]-tornei[i].prezzo+tornei[i].premio);
		}

		ma[i] = max(ma[i-1], dp[i]);
	}

	cout << max(ma[n-1],m) << "\n";

	return 0;
}
