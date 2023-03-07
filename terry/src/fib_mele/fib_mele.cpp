#include <iostream>
#include <algorithm>

using namespace std;

int solve()
{
	int n,m,c; cin >> n >> m >> c;
	return min(n*m, c);
}

int main()
{
	int T; cin >> T;
	for (int t = 1; t <= T; ++t)
	{
		cout << "Case #" << t << ": " << solve() << "\n";
	}
}
