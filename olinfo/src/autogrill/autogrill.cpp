#include <set>

using namespace std;

set<long long> grills;

void inizia() {}

void apri(long long p)
{
	grills.insert(p);
}

void chiudi(long long p)
{
	grills.erase(p);
}

long long chiedi(long long p)
{
	auto it = grills.lower_bound(p);
	long long right = (it != grills.end() ? *it : -1);
	if (it == grills.begin()) return right;
	--it;
	long long left = *it;
	if (right == -1) return left;
	if (p - left < right - p) return left;
	else return right;
}
