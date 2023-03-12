#include <vector>

using namespace std;

void scavi(int R, int C, int Q, vector<int>& x1, vector<int>& y1, vector<int>& x2, vector<int>& y2, vector<int>& p, vector<vector<int>>& terreno)
{
	for (int i = 0; i < Q; ++i)
	{
		terreno[x1[i]][y1[i]] += p[i];
		if (x2[i] < R-1)
			terreno[x2[i]+1][y1[i]] -= p[i];
		if (y2[i] < C-1)
			terreno[x1[i]][y2[i]+1] -= p[i];
		if (x2[i] < R-1 && y2[i] < C-1)
			terreno[x2[i]+1][y2[i]+1] += p[i];
	}
	for (int i = 0; i < R; ++i)
	{
		int curr = 0;
		for (int j = 0; j < C; ++j)
		{
			curr += terreno[i][j];
			terreno[i][j] = curr;
		}
	}
	for (int j = 0; j < C; ++j)
	{
		int curr = 0;
		for (int i = 0; i < R; ++i)
		{
			curr += terreno[i][j];
			terreno[i][j] = curr;
		}
	}
}
