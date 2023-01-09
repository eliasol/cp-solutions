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

#define MAXT 1000000

int N,T;
pair<int,int> st[MAXT];
int lz[MAXT];

pair<int,int> merge(pair<int,int> p1, pair<int,int> p2)
{
	if (p1.second > p2.second) return p1;
	if (p2.second > p1.second) return p2;
	if (p1.first < p2.first) return p1;
	return p2;
}

void push(int x, int l, int r)
{
	assert(l < r);
	if (lz[x])
	{
		lz[2*x] += lz[x];
		lz[2*x+1] += lz[x];
		st[2*x].second += lz[x];
		st[2*x+1].second += lz[x];
		lz[x] = 0;
	}
}

pair<int,int> get_max(int a, int b, int x, int l, int r)
{
	assert(!(a > r || b < l));
	if (a <= l && b >= r) return st[x];
	push(x,l,r);
	int m = (l+r)/2;
	pair<int,int> ans = {-1,-1};
	if (a <= m) ans = merge(ans, get_max(a,b,2*x,l,m));
	if (b > m) ans = merge(ans, get_max(a,b,2*x+1,m+1,r));
	return ans;
}

void add(int a, int b, int v, int x, int l, int r)
{
	if (a <= l && b >= r)
	{
		lz[x] += v;
		st[x].second += v;
		return;
	}
	push(x,l,r);
	int m = (l+r)/2;
	if (a <= m) add(a,b,v,2*x,l,m);
	if (b > m) add(a,b,v,2*x+1,m+1,r);
	st[x] = merge(st[2*x],st[2*x+1]);
}

int main()
{
	init_io();

	cin >> N;
	T = 1 << (int)ceil(log2(200001));
	for (int i = T; i < 2*T; ++i) st[i].first = i-T+1;
	for (int i = T-1; i > 0; --i) st[i] = merge(st[2*i],st[2*i+1]);

	vector<int> pos(N);
	for (auto &i : pos) cin >> i;

	auto add_trip = [&](int a, int b) {
		if (b > a) add(a+1,b,1,1,1,T);
		else add(b,a-1,1,1,1,T);
	};

	auto rem_trip = [&](int a, int b) {
		if (b > a) add(a+1,b,-1,1,1,T);
		else add(b,a-1,-1,1,1,T);
	};

	add(pos[0],pos[0],1,1,1,T);
	for (int i = 1; i < N; ++i)
	{
		add_trip(pos[i-1],pos[i]);
	}

	int Q; cin >> Q;
	while (Q--)
	{
		int f,v; cin >> f >> v;
		if (f == 0)
		{
			add(pos[0],pos[0],-1,1,1,T);
			rem_trip(pos[0],pos[1]);
			pos[0] = v;
			add(pos[0],pos[0],1,1,1,T);
			add_trip(pos[0],pos[1]);
		}
		else if (f == N-1)
		{
			rem_trip(pos[N-2],pos[N-1]);
			pos[N-1] = v;
			add_trip(pos[N-2],pos[N-1]);
		}
		else
		{
			rem_trip(pos[f-1],pos[f]);
			rem_trip(pos[f],pos[f+1]);
			pos[f] = v;
			add_trip(pos[f-1],pos[f]);
			add_trip(pos[f],pos[f+1]);
		}
		pair<int,int> ans = get_max(1,T,1,1,T);
		cout << ans.first << " " << ans.second << "\n";
	}

	return 0;
}
