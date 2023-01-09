#include <bits/stdc++.h>

using namespace std;

void valuta(int N, int C[], int L[], int P[])
{
	vector<pair<int,int>> to(N);
	to[0] = {0,0};
	for (int i = 1; i < N; ++i)
	{
		to[i].first = to[i-1].first + max(0, L[i-1] - (to[i-1].second + C[i-1]));
		to[i].second = to[i-1].second + C[i-1] - L[i-1] + to[i].first - to[i-1].first;
	}
	vector<pair<int,int>> from(N);
	from[N-1] = {max(0, L[N-1] - C[N-1]), max(0, C[N-1] - L[N-1])};
	for (int i = N-2; i >= 0; --i)
	{
		from[i].first = max(0, L[i] + from[i+1].first - C[i]);
		from[i].second = from[i].first + C[i] - L[i] - from[i+1].first + from[i+1].second;
	}
	for (int i = 0; i < N; ++i)
	{
		P[i] = from[i].first > 0 ? 0 : (from[i].second >= to[i].first ? 1 : 0);
	}
}
