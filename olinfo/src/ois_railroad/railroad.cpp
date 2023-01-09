#include <bits/stdc++.h>

using namespace std;

using pii = pair<int,int>;
using pli = pair<long long, int>;

int main()
{
	int n,m; cin >> n >> m;

	vector<tuple<int,int,int>> edges;
	vector<vector<pii>> graph(n);

	for (int i = 0; i < m; ++i)
	{
		int a,b,c; cin >> a >> b >> c;
		graph[a].push_back({b,c});
		graph[b].push_back({a,c});
		edges.push_back({a,b,c});
	}

	vector<bool> vis(n, false);
	priority_queue<pli, vector<pli>, greater<pli>> pq;

	vector<long long> distOrigine(n, 1e17);
	vector<int> prec(n,-1);
	distOrigine[0] = 0;
	pq.push({0,0});

	while (!pq.empty())
	{
		auto act = pq.top();
		pq.pop();
		if (vis[act.second]) continue;
		vis[act.second] = true;
		distOrigine[act.second] = act.first;
		for (auto& c : graph[act.second])
		{
			long long dist = act.first + c.second;
			if (dist < distOrigine[c.first])
			{
				pq.push({dist, c.first});
				distOrigine[c.first] = dist;
				prec[c.first] = act.second;
			}
		}
	}

	vector<bool> parte(n,false);
	int k = n-1;
	while (k != -1)
	{
		parte[k] = true;
		k = prec[k];
	}

	fill(vis.begin(), vis.end(), false);

	vector<long long> distDest(n, 1e17);
	distDest[n-1] = 0;
	pq.push({0,n-1});

	while (!pq.empty())
	{
		auto act = pq.top();
		pq.pop();
		if (vis[act.second]) continue;
		vis[act.second] = true;
		distDest[act.second] = act.first;
		for (auto& c : graph[act.second])
		{
			long long dist = act.first + c.second;
			pq.push({dist, c.first});
		}
	}

	long long best = LLONG_MAX;

	for (auto& edge : edges)
	{
		if (parte[get<0>(edge)] && parte[get<1>(edge)]) continue;
		long long shortest = min(distOrigine[get<0>(edge)] + distDest[get<1>(edge)], distOrigine[get<1>(edge)] + distDest[get<0>(edge)]) + get<2>(edge);
		if (shortest - distDest[0] < get<2>(edge)-1)
			best = min(best, shortest - distDest[0] + 1);
	}

	cout << (best == LLONG_MAX ? -1 : best) << "\n";
}
