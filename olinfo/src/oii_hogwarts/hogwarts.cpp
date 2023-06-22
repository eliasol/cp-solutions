#include <vector>
#include <utility>
#include <limits>
#include <queue>

using namespace std;

#define pii pair<int,int>

struct scala
{
	int a,inizio,fine;
};

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[])
{
	vector<vector<scala>> graph(N);

	for (int i = 0; i < M; i++)
	{
		graph[A[i]].push_back({B[i],inizio[i],fine[i]});
		graph[B[i]].push_back({A[i],inizio[i],fine[i]});
	}

	vector<int> t(N,numeric_limits<int>::max());
	vector<bool> vis(N,0);
	priority_queue<pii,vector<pii>,greater<pii>> pq;

	t[0] = 0;
	pq.push({0,0});

	while (!pq.empty())
	{
		int stanza = pq.top().second; pq.pop();
		if (vis[stanza]) continue;
		vis[stanza] = 1;
		if (stanza == N-1) return t[stanza];
		for (auto &sc : graph[stanza])
		{
			if (t[stanza] >= sc.fine) continue;
			int tmp = max(t[stanza], sc.inizio) + 1;
			if (tmp < t[sc.a])
			{
				t[sc.a] = tmp;
				pq.push({tmp, sc.a});
			}
		}
	}

	return -1;
}

