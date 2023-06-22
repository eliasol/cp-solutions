#include <vector>
#include <queue>

using namespace std;

long long smaltisci(int N, int M, vector<int> A, vector<vector<int>> B)
{
	vector<vector<int>> graph(N+M);

	vector<int> r(M);
	vector<long long> dist(N+M,0);
	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> q;

	for (int i = 0; i < M; ++i)
	{
		graph[N+i].push_back(A[i]);
		for (int j : B[i])
			graph[j].push_back(N+i);
		if (B[i].size() == 0)
			q.push({1,N+i});
		dist[N+i] = 1;
		r[i] = B[i].size();
	}

	vector<bool> vis(N+M, false);

	while (!q.empty())
	{
		auto [dt,id] = q.top();
		q.pop();

		if (id == 0)
			return dist[id]/2;

		if (vis[id]) continue;
		vis[id] = true;

		if (id < N)
		{
			for (int c : graph[id])
			{
				if (vis[c]) continue;
				dist[c] += dist[id];
				if (--r[c-N] == 0)
					q.push({dist[c],c});
			}
		}
		else
		{
			for (int c : graph[id])
			{
				if (vis[c]) continue;
				dist[c] = dist[id]+1;
				q.push({dist[c],c});
			}
		}
	}

	return -1;
}
