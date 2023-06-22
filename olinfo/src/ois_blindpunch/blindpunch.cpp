#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <queue>

#define MAXN 200000

using namespace std;

int T, N, K, i, j;
long double prob[MAXN];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	assert(1 == scanf("%d", &T));
	for(i=0; i<T; i++) {
		assert(2 == scanf("%d %d", &N, &K));

		long double result = 0;
		priority_queue<pair<long double,int>> pq;

		for(j=0; j<N; j++)
			assert(1 == scanf("%Lf", &prob[j])), pq.push({prob[j],j});

		while (K--)
		{
			auto top = pq.top(); pq.pop();
			result += top.first;
			pq.push({top.first*(1-prob[top.second]),top.second});
		}

		result = floor(result * 1000000) / 1000000;
		printf("%.6Lf\n", result);

	}

	return 0;
}
