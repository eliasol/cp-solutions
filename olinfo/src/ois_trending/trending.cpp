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

	int n,k; cin >> n >> k;

	struct cmp
	{
		bool operator()(const pair<int,string>& p1, const pair<int,string>& p2) const
		{
			if (p1.first == p2.first) return p1.second > p2.second;
			return p1.first < p2.first;
		}
	};

	unordered_map<string,int> cnt;
	set<pair<int,string>,cmp> st;
	deque<string> q;

	for (int i = 0; i < k; ++i,--n)
	{
		string s; cin >> s;
		q.push_back(s);
		if (cnt.count(s)) st.erase({cnt[s],s});
		++cnt[s];
		st.insert({cnt[s],s});
	}

	cout << st.rbegin()->second << "\n";

	while (n--)
	{
		string s = q.front(); q.pop_front();
		st.erase({cnt[s],s});
		--cnt[s];
		st.insert({cnt[s],s});
		cin >> s;
		q.push_back(s);
		if (cnt.count(s)) st.erase({cnt[s],s});
		++cnt[s];
		st.insert({cnt[s],s});

		cout << st.rbegin()->second << "\n";
	}

	return 0;
}
