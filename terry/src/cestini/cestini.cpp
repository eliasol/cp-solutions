#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve(int t)
{
	int N, M, Q;
	cin >> N >> M >> Q;

	string S;
	cin >> S;

	vector<vector<char>> v(M);
	for (char c : S)
		v[0].push_back(c);

	string risposta;

	for (int i = 0; i < Q; i++)
	{
		char type;
		int a, b;
		cin >> type >> a >> b;

		if (type == 's')
		{
			v[b].push_back(v[a].back());
			v[a].pop_back();
		}
		else
		{
			risposta.push_back(v[a][b]);
		}
	}


	cout << "Case #" << t << ": " << risposta << endl;
}

int main()
{
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		solve(t);
	}

	return 0;
}
