#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

void solve(int t)
{
	int N1, N2, N3, N4;
	cin >> N1 >> N2 >> N3 >> N4;

	int M;
	cin >> M;

	string F1, F2, F3, F4;
	cin >> F1 >> F2 >> F3 >> F4;

	int p1, p2, p3, p4;

	for (p1 = 0; p1 < N1; ++p1)
	{
		for (p2 = 0; p2 < N2; ++p2)
		{
			for (p3 = 0; p3 < N3; ++p3)
			{
				for (p4 = 0; p4 < N4; ++p4)
				{
					for (int i = 0; i < M; ++i)
						if (F1[p1+i] != F2[p2+i] || F2[p2+i] != F3[p3+i] || F3[p3+i] != F4[p4+i])
							goto skip;
					goto end;
					skip:;
				}
			}
		}
	}

	end:
	cout << "Case #" << t << ": " << p1 << " " << p2 << " " << p3 << " " << p4 << endl;
}

int main()
{
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		solve(t);
	}
}
