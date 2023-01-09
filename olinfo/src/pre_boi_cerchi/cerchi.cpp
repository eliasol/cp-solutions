#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct point
{
	long long x,y;

	point() = default;
	point(long long x, long long y) : x(x), y(y) {}

	point operator+(const point& p) const { return point(x + p.x, y + p.y); }
	point operator-(const point& p) const { return point(x - p.x, y - p.y); }
	long long operator^(const point& p) const { return x*p.y - y*p.x; }
};

vector<int> trovacerchi(int N, vector<int> X, vector<int> Y)
{
	vector<point> points(N+1);
	for (int i = 0; i < N; ++i) points[i] = point(X[i],Y[i]);
	points[N] = point(0,0);

	vector<int> order(N+1);
	iota(order.begin(), order.end(), 0);

	sort(order.begin(), order.end(), [&](int a, int b) -> bool {
		if (points[a].x != points[b].x) return points[a].x < points[b].x;
		return points[a].y < points[b].y;
	});

	vector<int> ans,tmp;

	for (int i : order)
	{
		while (tmp.size() > 1)
		{
			int i1 = tmp.back();
			int i2 = tmp[tmp.size()-2];
			if ((points[i1] - points[i2] ^ points[i] - points[i2]) <= 0)
				tmp.pop_back();
			else
				break;
		}
		tmp.push_back(i);
	}

	for (int x : tmp)
		if (x != N)
			ans.push_back(x);
	
	tmp.clear();

	for (int i : order)
	{
		while (tmp.size() > 1)
		{
			int i1 = tmp.back();
			int i2 = tmp[tmp.size()-2];
			if ((points[i1] - points[i2] ^ points[i] - points[i2]) >= 0)
				tmp.pop_back();
			else
				break;
		}
		tmp.push_back(i);
	}

	for (int i = 1; i < tmp.size()-1; ++i)
		if (tmp[i] != N)
			ans.push_back(tmp[i]);

	return ans;
}
