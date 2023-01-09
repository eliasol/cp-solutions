#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pii pair<int,int>
#define init_io() cin.sync_with_stdio(0); cin.tie(0); cout.sync_with_stdio(0); cout.tie(0)

#define FILE_IO_LOCAL 1
#define FILE_IO_JUDGE 1

#if FILE_IO_LOCAL && !defined(EVAL) || FILE_IO_JUDGE && defined(EVAL)
ifstream fin("input.txt");
ofstream fout("output.txt");
#define cin fin
#define cout fout
#endif

const int INF = numeric_limits<int>::max();

struct road
{
	int to, length;
	bool explode;
};

int main()
{
	init_io();

	int n,m,t;
	cin >> n >> m >> t;

	vector<vector<road>> g(n);

	for (int i = 0; i < m; i++)
	{
		int from, to, length, explode;
		cin >> from >> to >> length >> explode;
		g[from].push_back(road{to,length,explode == 1});
	}

	vector<int> nodi(n, INF);
	vector<bool> vis(n, 0);
	nodi[0] = 0;

	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0,0});

	while (!pq.empty())
	{
		int nodo = pq.top().second;
		pq.pop();

		if (vis[nodo]) continue;
		vis[nodo] = 1;

		for (auto &r : g[nodo])
		{
			int dist = nodi[nodo] + r.length;
			if (dist < nodi[r.to] && (dist <= t || !r.explode))
			{
				nodi[r.to] = dist;
				pq.push({dist, r.to});
			}
		}
	}

	cout << (nodi[n-1] == INF ? -1 : nodi[n-1]) << "\n";
	
	return 0;
}
