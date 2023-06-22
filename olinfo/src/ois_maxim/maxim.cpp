#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int N, K;
	fin >> N >> K;
	std::vector<int> V(N);
	for (int& i : V)
		fin >> i;
	std::multiset<int> curr;
	int l = 0, r = 0;
	int ans = 0;
	for (int i = 0; i < N; ++i)
	{
		while (r < N && r <= i + K)
			curr.insert(V[r++]);
		while (l < i - K)
			curr.erase(curr.find(V[l++]));
		ans = std::max(ans, *curr.rbegin() - V[i]);
	}
	fout << ans << "\n";
}
