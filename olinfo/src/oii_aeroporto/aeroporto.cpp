#include <algorithm>

using namespace std;

bool test(int k, int R, int A[], int B[])
{
	int last = A[0];
	for (int i = 1; i < R; ++i)
	{
		if (B[i] - last < k) return false;
		last = max(last+k, A[i]);
	}
	return true;
}

void pianifica(int R, int A[], int B[], int T[])
{
	int l = 1, r = 1e9;
	while (l != r)
	{
		int m = (l+r+1)/2;
		if (test(m,R,A,B)) l = m;
		else r = m-1;
	}
	T[0] = A[0];
	for (int i = 1; i < R; ++i) T[i] = max(T[i-1]+l, A[i]);
}
