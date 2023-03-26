#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static constexpr int MOD = 1e9+7;

int main()
{
	int n;
	cin >> n;

	vector<int> a(n), b(n);
	for (int& i : a)
		cin >> i;
	for (int& i : b)
		cin >> i;

	sort(a.rbegin(), a.rend());
	sort(b.rbegin(), b.rend());
	
	int ans = 1;
	int x = 0;

	for (int i = 0; i < n; ++i)
	{
		while (x < n && b[i] <= a[x])
			++x;
		ans = ((long long) ans * (x - i)) % MOD;
	}

	cout << ans << "\n";

	return 0;
}
