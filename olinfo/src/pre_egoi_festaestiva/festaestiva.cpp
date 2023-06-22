#include <vector>
#include <map>

using namespace std;

int organizza(int N, int X, int Y, vector<int> A, vector<int> B)
{
	map<int,int> m;

	m[0] = 0;

	for (int i = 0; i < N; ++i)
	{
		++m[A[i]];
		--m[B[i]+1];
	}

	int ans = 2e9, act = 0;

	for (auto it = m.begin(); it != m.end(); ++it)
	{
		act += it->second;
		auto it2 = it;
		++it2;
		int fine = it2 != m.end() ? it2->first-1 : 1e9;
		if (!(it->first > Y || fine < X)) ans = min(ans, act);
	}

	return N-ans;
}
