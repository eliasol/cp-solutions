#include <vector>
#include <numeric>

int M;
std::vector<int> factors;
std::vector<int> prec;

void inizializza(int P, int M)
{
	::M = M;
	factors.resize(M + 1);
	std::iota(factors.begin(), factors.end(), 0);
	prec.resize(M + 1, -1);
	for (int i = 2; i <= M; ++i)
	{
		if (factors[i] != i)
			continue;
		for (int j = i; j <= M; j += i)
			factors[j] = i;
	}
}

int controlla(int checksum)
{
	int i = checksum;
	while (i != 1 && prec[factors[i]] == -1)
		i /= factors[i];
	if (i != 1)
		return prec[factors[i]];
	i = checksum;
	while (i != 1)
		prec[factors[i]] = checksum, i /= factors[i];
	return 0;
}
