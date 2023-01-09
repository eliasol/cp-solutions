#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main()
{
	int N,M; cin >> N >> M;
	vector<vector<int>> tris(N, vector<int>(M));	
	for (auto& i : tris)
		for (auto& j : i)
			cin >> j;
	
	function<bool(int,int)> check_tris = [&](int x, int y) -> bool {
		// Check horizontal
		if (y > 1 && tris[x][y-2] && tris[x][y-1])
			return true;
		if (y > 0 && y < M-1 && tris[x][y-1] && tris[x][y+1])
			return true;
		if (y < M-2 && tris[x][y+1] && tris[x][y+2])
			return true;
		// Check vertical
		if (x > 1 && tris[x-2][y] && tris[x-1][y])
			return true;
		if (x > 0 && x < N-1 && tris[x-1][y] && tris[x+1][y])
			return true;
		if (x < N-2 && tris[x+1][y] && tris[x+2][y])
			return true;
		// Check diagonal "back"
		if (x > 1 && y > 1 && tris[x-2][y-2] && tris[x-1][y-1])
			return true;
		if (x > 0 && y > 0 && x < N-1 && y < M-1 && tris[x-1][y-1] && tris[x+1][y+1])
			return true;
		if (x < N-2 && y < M-2 && tris[x+1][y+1] && tris[x+2][y+2])
			return true;
		// Check diagonal "forward"
		if (x > 1 && y < M-2 && tris[x-1][y+1] && tris[x-2][y+2])
			return true;
		if (x > 0 && y < M-1 && x < N-1 && y > 0 && tris[x-1][y+1] && tris[x+1][y-1])
			return true;
		if (x < N-2 && y > 1 && tris[x+1][y-1] && tris[x+2][y-2])
			return true;
		return false;
	};

	int best = 0;
	int act = 0;

	function<void(int,int)> bruteforce = [&](int x, int y) {
		int pos = (N-x-1)*((2*M+2)/3) + (2*(M-y)+2)/3;
		if (x == N || act + pos <= best)
		{
			best = max(best, act);
			return;
		}
		bruteforce(x + (y+1)/M, (y+1)%M);
		if (!tris[x][y] && !check_tris(x,y))
		{
			tris[x][y] = 1;
			++act;
			bruteforce(x + (y+1)/M, (y+1)%M);
			--act;
			tris[x][y] = 0;
		}
	};

	bruteforce(0,0);
	cout << best << endl;
	return 0;
}