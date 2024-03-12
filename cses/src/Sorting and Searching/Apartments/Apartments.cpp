#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	int N, M, K;
	std::cin >> N >> M >> K;
	std::vector<int> A(N), B(M);

	for (std::vector<int>* i : { &A, &B })
		for (int& j : *i)
			std::cin >> j;

	std::sort(A.begin(), A.end());
	std::sort(B.begin(), B.end());

	int i = 0, j = 0, ans = 0;
	while (i < N && j < M)
	{
		if (A[i] < B[j] - K)
			++i;
		else if (B[j] < A[i] - K)
			++j;
		else
			++i, ++j, ++ans;
	}

	std::cout << ans << std::endl;
}
