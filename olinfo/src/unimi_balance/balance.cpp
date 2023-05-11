#include <iostream>
#include <vector>
#include <array>

int main()
{
	int N;
	std::cin >> N;
	std::vector<std::vector<std::array<int, 2>>> tree(N);

	for (int i = 1; i < N; ++i)
	{
		int A, B;
		std::cin >> A >> B;
		tree[A].push_back({i, B});
	}

	long long ans = 0;

	auto dfs = [&N, &tree, &ans](int x, auto dfs) -> long long {
		long long sum = 0;
		long long max = 0;
		for (auto& c : tree[x])
		{
			long long subtree = dfs(c[0], dfs) + c[1];
			sum += subtree;
			max = std::max(max, subtree);
		}
		ans += tree[x].size() * max - sum;
		sum = tree[x].size() * max;
		return sum;
	};

	dfs(0, dfs);

	std::cout << ans << std::endl;
}
