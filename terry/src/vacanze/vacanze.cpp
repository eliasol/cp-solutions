#include <iostream>
#include <vector>
#include <array>

int solve()
{
	int N, M;
	std::cin >> N >> M;
	std::vector<std::vector<bool>> adj(N, std::vector<bool>(N, false));
	std::vector<std::array<int, 2>> edges;
	for (int i = 0; i < M; ++i)
	{
		int A, B;
		std::cin >> A >> B;
		adj[A][B] = adj[B][A] = true;
		edges.push_back({A, B});
	}
	int ans = 0;
	for (int i = 0; i < M; ++i)
	{
		for (int j = i + 1; j < M; ++j)
		{
			if (edges[i][0] == edges[j][0] || edges[i][0] == edges[j][1] || edges[i][1] == edges[j][0] || edges[i][1] == edges[j][1])
				continue;
			if ((adj[edges[i][0]][edges[j][0]] && adj[edges[i][1]][edges[j][1]] && !adj[edges[i][0]][edges[j][1]] && !adj[edges[i][1]][edges[j][0]]) ||
				(adj[edges[i][0]][edges[j][1]] && adj[edges[i][1]][edges[j][0]] && !adj[edges[i][0]][edges[j][0]] && !adj[edges[i][1]][edges[j][1]]))
				++ans;
		}
	}
	return ans / 2;
}

int main()
{
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; ++t)
		std::cout << "Case #" << t << ": " << solve() << "\n";
	return 0;
}
