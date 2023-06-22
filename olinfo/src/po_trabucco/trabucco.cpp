#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

int ContaPercorsi(int N, int M, int K, int* X, int* Y)
{
	vector<vector<int>> sic(N,vector<int>(M,INT_MAX));
	queue<pair<int,int>> q;

	for (int i = 0; i < K; ++i)
	{
		sic[X[i]][Y[i]] = 0;
		q.push({X[i],Y[i]});
	}

	while (!q.empty())
	{
		auto p = q.front(); q.pop();
		int nsic = sic[p.first][p.second] + 1;
		if (p.first > 0 && sic[p.first-1][p.second] == INT_MAX)
		{
			sic[p.first-1][p.second] = nsic;
			q.push({p.first-1,p.second});
		}
		if (p.first < N-1 && sic[p.first+1][p.second] == INT_MAX)
		{
			sic[p.first+1][p.second] = nsic;
			q.push({p.first+1,p.second});
		}
		if (p.second > 0 && sic[p.first][p.second-1] == INT_MAX)
		{
			sic[p.first][p.second-1] = nsic;
			q.push({p.first,p.second-1});
		}
		if (p.second < M-1 && sic[p.first][p.second+1] == INT_MAX)
		{
			sic[p.first][p.second+1] = nsic;
			q.push({p.first,p.second+1});
		}
	}

	vector<vector<int>> sicp(N,vector<int>(M,-1));

	sicp[0][0] = sic[0][0];

	function<int(int,int)> calc_sic = [&](int x, int y) -> int {
		if (sicp[x][y] != -1) return sicp[x][y];
		if (x > 0) sicp[x][y] = max(sicp[x][y], calc_sic(x-1,y));
		if (y > 0) sicp[x][y] = max(sicp[x][y], calc_sic(x,y-1));
		sicp[x][y] = min(sicp[x][y],sic[x][y]);
		return sicp[x][y];
	};

	int best_sec = calc_sic(N-1,M-1);

	vector<vector<int>> conta(N,vector<int>(M,-1));

	conta[0][0] = 1;

	function<int(int,int)> calc_num = [&](int x, int y) -> int {
		if (conta[x][y] != -1) return conta[x][y];
		if (sic[x][y] < best_sec) return conta[x][y] = 0;
		++conta[x][y];
		if (x > 0) conta[x][y] += calc_num(x-1,y);
		if (y > 0) conta[x][y] += calc_num(x,y-1);
		return conta[x][y] = conta[x][y]%MOD;
	};

	return calc_num(N-1,M-1);
}
