#include <bits/stdc++.h>

using namespace std;

bool check(int n, long long s, vector<int>& v)
{
	long long somma = 0;
	int conta = 0;
	int i = 0;
	while (i < v.size() && conta < n)
	{
		somma += v[i];
		if (somma == s)
		{
			++conta;
			somma = 0;
		}
		++i;
	}
	return conta == n;
}

int taglia(int N, vector<int> B)
{
	long long somma = 0;
	for (auto &i : B) somma += i;

	if (somma < 0)
	{
		for (auto &i : B) i = -i;
		somma = -somma;
	}

	long long s = somma;

	if (s%2 == 0 && check(2,somma/2,B)) return 2;
	if (s == 0) return -1;
	while (s%2 == 0) s /= 2;
	for (int i = 3; i <= N && s > 1; i+=2)
	{
		if (s%i == 0 && check(i,somma/i,B)) return i;
		while (s%i == 0) s /= i;
	}
	return -1;
}
