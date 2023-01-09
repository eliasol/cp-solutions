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

struct edge
{
	struct pointer
	{
		vector<vector<edge>>* v;
		int from;
		int i;

		pointer() : v(0) {}
		pointer(vector<vector<edge>>* p_v, int p_from, int p_i) : v(p_v), from(p_from), i(p_i) {}

		edge& operator*() const { return (*v)[from][i]; }
		edge* operator->() const { return &(*v)[from][i]; }
		operator bool() const { return v; }
	};

	int from;
	int to;
	int weight;
	pointer back;
};

int n;
vector<vector<edge>> graph;

void add_edge(int from, int to, int weight)
{
	edge real{
		from,
		to,
		weight,
		edge::pointer(&graph,to,(int)graph[to].size())
	};
	edge back{
		to,
		from,
		0,
		edge::pointer(&graph,from,(int)graph[from].size())
	};
	graph[from].push_back(real);
	graph[to].push_back(back);
}

bool bfs(int source, int sink, vector<int>& dist)
{
	dist.clear();
	dist.resize(graph.size(),-1);
	queue<pair<int,int>> q;
	dist[source] = 0;
	q.push({source,0});

	while (!q.empty())
	{
		auto i = q.front();
		q.pop();

		for (auto& c : graph[i.first])
		{
			if (c.weight == 0 || dist[c.to] != -1) continue;
			q.push({c.to,i.second+1});
			dist[c.to] = i.second+1;
		}
	}

	return dist[sink] != -1;
}

int sendflow(int source, int sink, vector<int>& dist, vector<int>& start, int flow = INT_MAX)
{
	if (source == sink) return flow;

	for (; start[source] < graph[source].size(); ++start[source])
	{
		edge& c = graph[source][start[source]];
		if (c.weight == 0 || dist[c.to] != dist[source]+1) continue;
		int lflow = sendflow(c.to,sink,dist,start,min(flow,c.weight));
		if (lflow)
		{
			c.weight -= lflow;
			c.back->weight += lflow;
			return lflow;
		}
	}

	return 0;
}

int maxflow(int source, int sink)
{
	int flow = 0;
	vector<int> dist,start;
	int best;

	while (best = bfs(source,sink,dist))
	{
		start.assign(graph.size(),0);
		int tmp;
		while (tmp = sendflow(source,sink,dist,start)) flow += tmp;
	}

	return flow;
}

int main()
{
	init_io();

	cin >> n;

	graph.resize(n+2);

	for (int i = 0; i < n; ++i)
	{
		int c; cin >> c;
		add_edge(0,i+1,c);
	}

	for (int i = 0; i < n; ++i)
	{
		int c; cin >> c;
		add_edge(i+1,n+1,c);
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int c; cin >> c;
			add_edge(i+1,j+1,c);
		}
	}

	cout << maxflow(0,n+1) << "\n";

	return 0;
}
