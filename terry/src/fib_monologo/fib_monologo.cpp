#include <iostream>
#include <vector>

using namespace std;

int solve()
{
	int n; cin >> n;
	vector<int> v(n);
	for (int& i : v)
		cin >> i;
	int ans = 0;
	for (int& i : v)
	{
		int x; cin >> x;
		ans += x != i;
	}
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
