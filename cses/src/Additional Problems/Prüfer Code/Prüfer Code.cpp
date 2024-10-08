#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> v(n - 2);
    std::vector<int> occ(n + 1);

    for (int& i : v)
    {
        std::cin >> i;
        ++occ[i];
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i = 1; i <= n; ++i)
        if (!occ[i])
            pq.push(i);
    
    int i = 0;
    
    while (i < n - 2)
    {
        int x = pq.top();
        pq.pop();

        std::cout << x << " " << v[i] << "\n";

        --occ[v[i]];

        if (!occ[v[i]])
            pq.push(v[i]);
        ++i;
    }

    assert(pq.size() == 2);

    int a = pq.top();
    pq.pop();
    int b = pq.top();

    std::cout << a << " " << b << "\n";
}