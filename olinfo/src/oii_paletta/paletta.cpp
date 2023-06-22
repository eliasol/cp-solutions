#include <vector>

int N;
std::vector<int> fw;

void add(int i, int v)
{
	++i;
	while (i <= N)
	{
		fw[i] += v;
		i += i&-i;
	}
}

int sum(int i)
{
	++i;
	int ans = 0;
	while (i > 0)
	{
		ans += fw[i];
		i -= i&-i;
	}
	return ans;
}

long long countInv(int N, const std::vector<int>& v)
{
	fw.assign(N + 1, 0);
	long long ans = 0;
	for (int i = v.size() - 1; i >= 0; --i)
	{
		ans += sum(v[i]);
		add(v[i], 1);
	}
	return ans;
}

long long paletta_sort(int N, int V[])
{
	::N = N;
	std::vector<int> v;
	for (int i = 0; i < N; i += 2)
	{
		if (V[i] % 2)
			return -1;
		v.push_back(V[i]);
	}
	long long ans = countInv(N, v);
	v.clear();
	for (int i = 1; i < N; i += 2)
	{
		if (V[i] % 2 == 0)
			return -1;
		v.push_back(V[i]);
	}
	ans += countInv(N, v);
	return ans;
}

