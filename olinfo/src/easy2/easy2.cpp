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
	int a,b;
	int ans = -1;

	while (n--)
	{
		cin >> a >> b;
		ans = (a+b)%2 ? ans : max(ans, a+b);
	}

	cout << ans << "\n";

	return 0;
}
