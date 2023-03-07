#include <iostream>
#include <array>

using namespace std;

int solve()
{
	int s; cin >> s;
	array<int, 4> dadi;
	for (int& i : dadi)
		cin >> i;
	for (int i = 0; i < dadi.size() && s > 0; ++i)
	{
		int tmp = min(s, dadi[i]);
		dadi[i] -= tmp;
		dadi.back() += tmp;
		s -= tmp;
	}
	int ans = 0;
	for (int i = 0; i < dadi.size(); ++i)
		ans += dadi[i] * (i+1);
	return ans;
}

int main()
{
	int T; cin >> T;
	for (int t = 1; t <= T; ++t)
	{
		cout << "Case #" << t << ": " << solve() << "\n";
	}
}
