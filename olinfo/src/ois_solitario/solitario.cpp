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

int N,M;
int ans = 0, xs = 0;
vector<vector<bool>> tbl;

bool check(int r, int c)
{
	if (c >= 2 && tbl[r][c-1] && tbl[r][c-2]) return true;
	if (r >= 2 && tbl[r-1][c] && tbl[r-2][c]) return true;
	if (c >= 2 && r >= 2 && tbl[r-1][c-1] && tbl[r-2][c-2]) return true;
	if (r >= 2 && c <= M-3 && tbl[r-1][c+1] && tbl[r-2][c+2]) return true;
	return false;
}

void solve(int r, int c)
{
	if (r >= N || c >= M)
	{
		ans = max(ans, xs);
		return;
	}
	int rimasti = r*M + c;
	if (xs + N*M - rimasti <= ans) return;
	solve(r + (c+1)/M, (c+1)%M);
	if (check(r,c))
	{
		ans = max(ans, xs);
		return;
	}
	++xs;
	tbl[r][c] = 1;
	solve(r + (c+1)/M, (c+1)%M);
	tbl[r][c] = 0;
	--xs;
}

int main()
{
	init_io();

	cin >> N >> M;
	tbl.resize(N, vector<bool>(M,0));

	solve(0,0);

	cout << ans << "\n";

	return 0;
}
