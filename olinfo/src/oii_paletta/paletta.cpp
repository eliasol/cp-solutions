#include <memory.h>
#include <assert.h>
#include <stdio.h>

int n;
long long fw[800000];

void add(int i, long long v)
{
	i += 1;
	for (; i <= n; i += i&(-i)) fw[i] += v;
}

long long sum(int i)
{
	i += 1;
	long long s = 0;
	for (; i > 0; i -= i&(-i)) s += fw[i];
	return s;
}

long long paletta_sort(int N, int V[]) {
	for (int i = 0; i < N; ++i)
		if (i%2 != V[i]%2) return -1;

	long long ans = 0;
	n = (N+1)/2;
	int v[n];
	for (int i = 0; i < N; i+=2) v[i/2] = V[i]/2;
	for (int i = n-1; i >= 0; --i)
	{
		ans += sum(v[i]);
		add(v[i],1);
	}
	n = N/2;
	memset(fw,0,(n+1)*sizeof(long long));
	for (int i = 1; i < N; i+=2) v[i/2] = V[i]/2;
	for (int i = n-1; i >= 0; --i)
	{
		ans += sum(v[i]);
		add(v[i],1);
	}
	return ans;
}

