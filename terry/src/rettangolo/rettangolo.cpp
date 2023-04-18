#include <iostream>

int main()
{
	int T;
	std::cin >> T;

	for (int i = 1; i <= T; ++i)
	{
		int x1, y1, x2, y2, x3, y3;
		std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		std::cout << "Case #" << i << ": " << (x1 ^ x2 ^ x3) << " " << (y1 ^ y2 ^ y3) << "\n";
	}

	return 0;
}
