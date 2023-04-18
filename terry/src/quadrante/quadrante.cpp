#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int main()
{
	int T;
	std::cin >> T;

	for (int i = 1; i <= T; ++i)
	{
		int N;
		std::cin >> N;
		std::vector<std::array<int, 3>> pts(N);
		for (int j = 0; j < N; ++j)
		{
			pts[j][2] = j;
			std::cin >> pts[j][0] >> pts[j][1];
		}
		std::sort(pts.begin(), pts.end());
		int l = 0, r = N + 1;
		while (r - l > 1)
		{
			int m = (l + r) / 2;
			int ok = true;
			std::array<int, 3> last = {0, 0, 0};
			for (int j = 0; j < N; ++j)
			{
				if (pts[j][2] < m)
				{
					if (last[1] > pts[j][1])
					{
						ok = false;
						break;
					}
					last = pts[j];
				}
			}
			if (ok)
				l = m;
			else
				r = m;
		}
		std::cout << "Case #" << i << ": " << l << "\n";
	}

	return 0;
}
