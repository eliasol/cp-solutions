#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

class modular_fenwick_tree
{
private:
	const int mod;
	std::vector<int> data;

public:
	modular_fenwick_tree(int n, int mod) : data(n+1, 0), mod(mod) {}
	void add(int i, int v)
	{
		++i;
		while (i < data.size())
		{
			data[i] = (data[i] + v) % mod;
			i += i&-i;
		}
	}
	int sum(int i)
	{
		++i;
		int sum = 0;
		while (i > 0)
		{
			sum = (sum + data[i]) % mod;
			i -= i&-i;
		}
		return sum;
	}
};

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	int n;
	fin >> n;
	std::vector<int> v(n);
	for (int& i : v)
		fin >> i;
	std::vector<int> order(n);
	std::iota(order.begin(), order.end(), 0);
	std::sort(order.begin(), order.end(), [&v](const int& a, const int& b) -> bool {
		if (v[a] == v[b])
			return a > b;
		return v[a] < v[b];
	});
	modular_fenwick_tree fw(n, 1e9+7);
	for (int i = 0; i < n; ++i)
	{
		fw.add(order[i], fw.sum(order[i]-1) + 1);
	}
	fout << fw.sum(n-1) << "\n";
	return 0;
}
