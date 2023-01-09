#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define init_io() cin.sync_with_stdio(0); cin.tie(0); cout.sync_with_stdio(0); cout.tie(0)

#define FILE_IO_LOCAL 0
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

	int n; cin >> n;

	unordered_map<int,int> dist;
	queue<int> q;
	dist[n] = 0;
	q.push(n);

	auto add = [&dist,&q](int x, int d) {
		if (x == 0)
		{
			cout << d << "\n";
			exit(0);
		}
		if (x > 1e9 || dist.count(x)) return;
		dist[x] = d;
		q.push(x);
	};

	while (!q.empty())
	{
		int act = q.front(); q.pop();
		int d = dist[act] + 1;
		add(act+1,d);
		add(act-1,d);
		add(2*act,d);
		while (act % 3 == 0)
		{
			act /= 3;
			add(act,d);
		}
	}

	return 0;
}
