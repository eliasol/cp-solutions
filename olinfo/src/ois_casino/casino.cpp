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

constexpr int p = 31;
constexpr int mod = 1e9+7;

int main()
{
	init_io();

	int n,m; cin >> n >> m;
	
	vector<int> pows(2*m);
	pows[0] = 1;
	for (int i = 1; i < pows.size(); ++i)
		pows[i] = (pows[i-1] * (ll) p) % mod;

	long long ans = 0;
	
	unordered_map<int, int> hashes;
	while (n--)
	{
		string s; cin >> s;
		int hash = 0;
		for (int i = 0; i < m; ++i)
			hash = (hash + (s[i] - 'a' + 1) * (ll) pows[i]) % mod;
		int minhash = (hash * (ll) pows[m]) % mod;
		for (int i = 0; i < m - 1; ++i)
		{
			hash = (hash + mod - (((s[i] - 'a' + 1) * (ll) pows[i]) % mod)) % mod;
			hash = (hash + (s[i] - 'a' + 1) * (ll) pows[m+i]) % mod;
			minhash = min(minhash, (int) ((pows[m-i-1] * (ll) hash) % mod));
		}
		ans += (hashes[minhash]++);
	}

	cout << ans << "\n";

	return 0;
}
