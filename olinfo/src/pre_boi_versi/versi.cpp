#include <vector>
#include <algorithm>

using namespace std;

int getlimit(int N, vector<int>& A, vector<int>& B)
{
	int last = 0;
	for (int k = 1; k <= N; ++k)
	{
		while (last < N && B[last] < A[k-1]) ++last;
		if (last >= N) return k-1;
		++last;
	}
	return N;
}

int direziona(int N, vector<int> A, vector<int> B) 
{
	int a = getlimit(N,A,B);
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	for (auto &i : A) i = -i;
	for (auto &i : B) i = -i;
	int b = N-getlimit(N,A,B);
	return a-b+1;
}
