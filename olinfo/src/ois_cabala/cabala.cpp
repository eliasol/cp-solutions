#include <fstream>
#include <algorithm>
#include <array>

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int T, N, M;
	std::array<int, 3> digits = {3, 6, 9};

	long long best = 0;

	auto brute = [&](int d, long long act, auto brute)
	{
		best = std::max(best, act % M);
		if (d == 0)
			return;
		int ld = act % 10;
		for (int i : digits)
		{
			if (i == ld)
				continue;
			brute(d - 1, 10 * act + i, brute);
		}
	};

	fin >> T;
	while (T--)
	{
		best = 0;
		fin >> N >> M;
		brute(N, 0, brute);
		fout << best << " ";
	}
	return 0;
}
