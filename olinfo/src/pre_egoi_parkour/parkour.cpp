#include <vector>
#include <assert.h>

using namespace std;

int n;
vector<int> dp, sp;

bool check(vector<int>& s, vector<int>& a, vector<int>& b, int h)
{
	for (int i = n-1; i >= 0; --i)
	{
		if (s[i] > h)
		{
			dp[i] = 0;
			sp[i] = sp[i+1];
			continue;
		}
		dp[i] = (sp[i+a[i]]-sp[i+b[i]+1] > 0);
		sp[i] = sp[i+1] + dp[i];
	}
	return dp[0] > 0;
}

int salta(int N, vector<int> S, vector<int> A, vector<int> B)
{
	n = N;
	dp.resize(n+1); sp.resize(n+2);
	S.push_back(0);
	dp[n] = 1;
	sp[n+1] = 0;
	sp[n] = 1;

	int l = S[0], r = 1e6;

	while (l != r)
	{
		int m = (l+r)/2;
		if (check(S,A,B,m)) r = m;
		else l = m+1;
	}

	return l;
}