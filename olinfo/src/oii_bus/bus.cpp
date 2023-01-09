#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int pianifica(int N, int L, vector<vector<int>> F)
{
	vector<unordered_map<int,int>> g(N);
	
	for (int i = 0; i < L; ++i)
		for (int j = F[i].size()-1; j >= 0; --j)
			g[F[i][j]][i] = j;
	
	vector<int> dist(N, -1);
	queue<int> q;
	dist[0] = 0;
	q.push(0);

	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		if (x == N-1) return dist[x] - 1;
		for (auto& [i,j] : g[x])
		{
			if (F[i].size() <= j) continue;
			while (F[i].size() > j)
			{
				int k = F[i].back();
				if (dist[k] == -1)
				{
					dist[k] = dist[x] + 1;
					q.push(k);
				}
				F[i].pop_back();
			}
		}
	}

	return -1;
}
