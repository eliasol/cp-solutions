#include <iostream>

int main()
{
	int N;
	std::cin >> N;

	if (N % 4 != 0 && N % 4 != 3)
		return std::cout << "NO\n", 0;

	std::cout << "YES\n" << (N + 1) / 2 << "\n";

	for (int i = (N % 4 ? 0 : 1); i < N; i += 4)
		std::cout << i + 1 << " " << i + 2 << " ";
	std::cout << "\n" << N / 2 << "\n";

	if (N % 4 == 3)
		std::cout << 3 << " ";
	for (int i = (N % 4 ? 4 : 1); i < N; i += 4)
		std::cout << i << " " << i + 3 << " ";
	std::cout << "\n";
}
