#include <algorithm>

void permute(int subtask, int N, int V[], int R[])
{
	std::sort(V, V + N);

	int l = 0, r = N;
	for (int i = 0; i < N; i += 2)
		R[i] = V[--r];
	for (int i = 1; i < N; i += 2)
		R[i] = V[l++];
}
