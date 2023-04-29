#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solve()
{
	int n; cin >> n;
	string s; cin >> s;
	vector<int> zeros;
	zeros.push_back(-1);
	for (int i = 0; i < s.length(); ++i)
		if (s[i] == '0')
			zeros.push_back(i);
	zeros.push_back(s.length());
	int best = zeros[1] - zeros[0] - 1;
	for (int i = 0; i < zeros.size() - 2; ++i)
		best = max(best, zeros[i+2] - zeros[i] - 1);
	return best;
}

int main()
{
	int T; cin >> T;
	for (int t = 1; t <= T; ++t)
	{
		cout << "Case #" << t << ": " << solve() << "\n";
	}
}
