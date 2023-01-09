#include <vector>
#include <queue>

using namespace std;

#define pii pair<int,int>

void mincammino(int n, int m, vector<int> x, vector<int> y, vector<int> p, vector<int> &d) 
{
	vector<vector<pii>> g(n);

	for (int i = 0; i < m; ++i) g[x[i]].push_back({y[i],p[i]});
	d.assign(n, -1);

	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0,0});

	while (!pq.empty())
	{
		pii top = pq.top(); pq.pop();
		if (d[top.second] != -1) continue;
		d[top.second] = top.first;

		for (auto &child : g[top.second]) pq.push({d[top.second] + child.second, child.first});
	}
}
