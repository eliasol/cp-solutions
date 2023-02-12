#include <iostream>
#include <vector>

class fenwick_tree
{
private:
	int n;
	std::vector<int> data;
public:
	fenwick_tree(int n) : n(n), data(n+1,0) {}
	void add(int i, int v)
	{
		++i;
		while (i <= n)
		{
			data[i] += v;
			i += i&-i;
		}
	}
	int sum(int i)
	{
		++i;
		int res = 0;
		while (i > 0)
		{
			res += data[i];
			i -= i&-i;
		}
		return res;
	}
};

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> v(n);
	for (int& i : v)
		std::cin >> i;
	fenwick_tree fw(n+1);
	for (int i = n-1; i >= 0; --i)
	{
		int smaller = fw.sum(v[i]);
		int greater = i-v[i]+smaller+1;
		fw.add(v[i],1);
		v[i] = smaller + greater;
	}
	for (int i : v)
		std::cout << i << " ";
	return 0;
}
