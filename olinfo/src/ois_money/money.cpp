#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define init_io() cin.sync_with_stdio(0); cin.tie(0); cout.sync_with_stdio(0); cout.tie(0)

#define FILE_IO_LOCAL 1
#define FILE_IO_JUDGE 1

#if FILE_IO_LOCAL && !defined(EVAL) || FILE_IO_JUDGE && defined(EVAL)
ifstream fin("input.txt");
ofstream fout("output.txt");
#define cin fin
#define cout fout
#endif

int main()
{
	init_io();

	int n,m; cin >> n >> m;
	vector<int> arr(n,0);

	for (int i = 0; i < m; ++i)
	{
		int a,b,w; cin >> a >> b >> w;
		arr[a] -= w;
		arr[b] += w;
	}

	queue<pair<int,int>> ric, manda;
	for (int i = 0; i < n; ++i)
	{
		if (arr[i] > 0) manda.push({i,arr[i]});
		else if (arr[i] < 0) ric.push({i,arr[i]});
	}

	queue<tuple<int,int,int>> output;

	while (!manda.empty())
	{
		pair<int,int> i = manda.front(); manda.pop();
		pair<int,int> j = ric.front(); ric.pop();
		j.second += i.second;
		output.push({i.first, j.first, i.second});
		if (j.second > 0) manda.push(j);
		else if (j.second < 0) ric.push(j);
	}

	cout << output.size() << "\n";
	while (!output.empty())
	{
		auto i = output.front(); output.pop();
		cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << "\n";
	}

	return 0;
}
