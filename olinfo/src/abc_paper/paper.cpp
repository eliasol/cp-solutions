#include <vector>
#include <algorithm>

void dfs(const std::vector<std::vector<int>>& g, std::vector<bool>& vis, int x)
{
	if (vis[x])
		return;
	vis[x] = true;
	for (int c : g[x])
		dfs(g, vis, c);
}

int paper(int N, int M, int A[], int B[])
{
	std::vector<std::vector<int>> g(N + 1);

	for (int i = 0; i < M; ++i)
		g[A[i]].push_back(B[i]);

	std::vector<bool> vis(N + 1, false);

	int root;
	for (int i = 1; i <= N; ++i)
		if (!vis[i])
			root = i, dfs(g, vis, i);

	vis.assign(N + 1, false);
	dfs(g, vis, root);

	if (std::find(vis.begin() + 1, vis.end(), false) != vis.end())
		return 0;

	g.assign(N + 1, std::vector<int>());

	for (int i = 0; i < M; ++i)
		g[B[i]].push_back(A[i]);

	vis.assign(N + 1, false);
	dfs(g, vis, root);

	return std::count(vis.begin() + 1, vis.end(), true);
}
