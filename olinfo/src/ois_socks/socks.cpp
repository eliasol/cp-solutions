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

	int n,c; cin >> n >> c;

	long long swaps = 0;
	int next = c;
	unordered_map<int,int> pos;

	for (int i = 0; i < n; ++i)
	{
		int x; cin >> x;
		if (!pos.count(x))
			pos[x] = next--;
		swaps += c - pos[x];
	}

	cout << swaps << "\n";

	return 0;
}
