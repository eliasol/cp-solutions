#include <vector>
using namespace std;

int presta(int N, int C, vector<int> P) 
{
    vector<int> count(100001, 0);
    for (auto &i : P) ++count[i];
    int i = 0;
    for (int j = 100000; j >= 0; --j)
        while (count[j]--)
            P[i++] = j;
    int somma = 0;
    i = 0;
    while (somma < C) somma += P[i++];
    return i;
}
