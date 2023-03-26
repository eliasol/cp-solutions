#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n,x;
	cin >> n >> x;
	vector<int> v(n);
	for (int& i : v)
		cin >> i;
	sort(v.begin(), v.end());
	int i = 0;
	for (; i < n-1 && v[i] + v[i+1] <= x; i+=2);
	cout << i/2 + n - i << "\n";
	return 0;
}
