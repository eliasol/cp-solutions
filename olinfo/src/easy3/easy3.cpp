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

int main()
{
	init_io();

	int n; cin >> n;
	int p1 = -1, p2 = -1, d1 = -1, d2 = -1;
	int x;

	while (n--)
	{
		cin >> x;
		if (x%2)
		{
			d2 = max(d2,x);
			if (d2 > d1) swap(d1,d2);
		}
		else
		{
			p2 = max(p2,x);
			if (p2 > p1) swap(p1,p2);
		}
	}

	cout << (p2 == -1 && d2 == -1 ? -1 : max(p1+p2,d1+d2)) << "\n";

	return 0;
}
