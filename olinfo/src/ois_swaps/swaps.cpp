#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
	int n;
	cin >> n;

	vector<int> v(n);
	for (int& i : v)
		cin >> i;

	int ans = n;
	int k = 0;
	vector<bool> vis(n, false);

	for(int i = 0; i < n; ++i)
	{
		k = gcd(k, abs(v[i]-v[v[i]-1]));
		if (vis[i])
			continue;
		--ans;
		int x = i;
		for (; !vis[x]; vis[x] = true, x = v[x]-1);
	}

	for (int i = 1; i <= n; ++i)
		cout << (k % i ? -1 : ans) << " ";
	cout << "\n";
	return 0;
}
