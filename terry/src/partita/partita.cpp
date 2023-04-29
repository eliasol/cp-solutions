#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solve()
{
	int n,k; cin >> n >> k;
	vector<int> r(n);

	for (int& i : r)
		cin >> i;

	priority_queue<int> pq;

	for (int i = 0; i < n; ++i)
	{
		pq.push(r[i]);
		while (!pq.empty() && k == 1)
		{
			k += pq.top();
			pq.pop();
		}
		if (k == 1)
			return -1;
		--k;
	}

	return n - pq.size();
}

int main()
{
	int T; cin >> T;
	for (int t = 1; t <= T; ++t)
	{
		cout << "Case #" << t << ": " << solve() << "\n";
	}
}
