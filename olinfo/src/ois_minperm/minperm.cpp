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

struct dsu
{
	int sets;
	vector<int> tree;

	dsu(int n) : sets(n), tree(n,-1) {}

	int get_group(int x)
	{
		if (tree[x] < 0) return x;
		return tree[x] = get_group(tree[x]);
	}

	void merge(int a, int b)
	{
		a = get_group(a); b = get_group(b);
		if (a == b) return;
		--sets;
		if (tree[a] < tree[b]) tree[b] = a;
		else if (tree[b] < tree[a]) tree[a] = b;
		else
		{
			tree[a] = b;
			--tree[b];
		}
	}
};

struct group
{
	vector<int> val, pos;
};

int main()
{
	init_io();

	int n,k; cin >> n >> k;

	vector<int> p(n),l(k);
	for (auto &i : p) cin >> i;
	for (auto &i : l) cin >> i;

	dsu d(n);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < k; ++j)
			if (i + l[j] < n)
				d.merge(i, i + l[j]);

	vector<group> groups(n);

	for (int i = 0; i < n; ++i)
	{
		groups[d.get_group(i)].pos.push_back(i);
		groups[d.get_group(i)].val.push_back(p[i]);
	}

	for (auto &i : groups)
	{
		sort(i.val.begin(), i.val.end());
		for (int j = 0; j < i.val.size(); ++j) p[i.pos[j]] = i.val[j];
	}

	for (auto &i : p) cout << i << " ";
	cout << "\n";

	return 0;
}
