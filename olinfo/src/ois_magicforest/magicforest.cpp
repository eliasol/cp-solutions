#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

constexpr unsigned int MOD = 1e9+7;

struct edge { int a, b, weight; };
bool operator<(const edge& e1, const edge& e2) { return e1.weight < e2.weight; }

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n,m;
	cin >> n >> m;

	vector<edge> edges(m);
	for (edge& i : edges)
		cin >> i.a >> i.b >> i.weight;

	sort(edges.begin(), edges.end());

	vector<unordered_map<int, unsigned int>> continues(n+1);

	unsigned int conta = 0;

	for (const edge& curr : edges)
	{
		++conta;
		++continues[curr.a][curr.weight+1];
		++continues[curr.b][curr.weight+1];
		if (continues[curr.a].count(curr.weight) > 0)
		{
			conta += continues[curr.a][curr.weight];
			continues[curr.b][curr.weight+1] += continues[curr.a][curr.weight];
		}
		if (continues[curr.b].count(curr.weight) > 0)
		{
			conta += continues[curr.b][curr.weight];
			continues[curr.a][curr.weight+1] += continues[curr.b][curr.weight];
		}
		continues[curr.a][curr.weight+1] %= MOD;
		continues[curr.b][curr.weight+1] %= MOD;
		conta %= MOD;
	}

	cout << conta << "\n";

	return 0;
}
