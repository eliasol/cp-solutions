#include <bits/stdc++.h>

using namespace std;

int Trova(int N, int K, int* insieme)
{
    if (K == 1) return 0;
    unordered_set<int> s;
    sort(insieme, insieme+N);
    int conta = 0;
    for (int i = 0; i < N; ++i)
    {
        if (s.count(insieme[i])) continue;
        s.insert(insieme[i]);
        s.insert(insieme[i]*K);
        ++conta;
    }
    return conta;
}
