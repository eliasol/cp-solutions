#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

class segment_tree
{
private:
	struct node
	{
		int first = 0, last = 0;
		long long sum = 0;
	};

	int n;
	vector<node> data;

	long long lower_bound(int v, int x, int l, int r)
	{
		if (data[x].last > v)
			return data[x].sum;
		if (data[x].first <= v)
			return 0LL;
		int m = (l+r)/2;
		long long tmp = lower_bound(v, 2*x+1, m, r);
		if (tmp != 0)
			return data[x].sum - data[2*x+1].sum + tmp;
		return lower_bound(v, 2*x, l, m);
	}

	void merge(int x, int l, int r)
	{
		int m = (l+r)/2;
		data[x].last = data[2*x+1].last;
		data[x].first = max(data[2*x].first, data[2*x+1].first);
		data[x].sum = data[2*x+1].sum + lower_bound(data[2*x+1].first, 2*x, l, m);
	}

	void build(int x, int l, int r, const vector<int>& v)
	{
		if (r - l <= 1)
		{
			data[x].first = data[x].last = data[x].sum = l >= v.size() ? 0 : v[l];
			return;
		}
		int m = (l+r)/2;
		build(2*x, l, m, v);
		build(2*x+1, m, r, v);
		merge(x, l, r);
	}

	void update(int i, int v, int x, int l, int r)
	{
		if (i < l || i >= r)
			return;
		if (r - l <= 1)
		{
			data[x].first = data[x].last = data[x].sum = v;
			return;
		}
		int m = (l+r)/2;
		update(i, v, 2*x, l, m);
		update(i, v, 2*x+1, m, r);
		merge(x, l, r);
	}

public:
	segment_tree(const vector<int>& v) : n(1 << (int)ceil(log2(v.size()))), data(2*n)
	{
		build(1, 0, n, v);
	}

	void update(int i, int v)
	{
		update(i, v, 1, 0, n);
	}

	long long get()
	{
		return data[1].sum;
	}
};

int main()
{
	int n, q;
	cin >> n >> q;

	vector<int> v(n);
	for (int& i : v)
		cin >> i;
	
	segment_tree st(v);

	while (q--)
	{
		int p, s; cin >> p >> s;
		st.update(p, s);
		cout << st.get() << "\n";
	}

	return 0;
}
