#include <iostream>
#include <vector>
#include <set>
#include <functional>

int main()
{
	int n, k;
	std::cin >> n >> k;

	std::vector<int> v(n);
	for (int& i : v)
		std::cin >> i;

	std::multiset<int> fhalf, shalf;

	std::function<void()> adjust = [&fhalf, &shalf] ()
	{
		while (shalf.size() > fhalf.size())
		{
			fhalf.insert(*shalf.begin());
			shalf.erase(shalf.begin());
		}

		while (fhalf.size() > shalf.size() + 1)
		{
			shalf.insert(*fhalf.rbegin());
			fhalf.erase(std::prev(fhalf.end()));
		}

		while (!shalf.empty() && *fhalf.rbegin() > *shalf.begin())
		{
			shalf.insert(*fhalf.rbegin());
			fhalf.erase(std::prev(fhalf.end()));
			fhalf.insert(*shalf.begin());
			shalf.erase(shalf.begin());
		}
	};

	fhalf.insert(v.begin(), v.begin() + k - 1);
	adjust();

	for (int i = k - 1; i < n; ++i)
	{
		fhalf.insert(v[i]);
		adjust();

		std::cout << *fhalf.rbegin() << " ";

		if (v[i - k + 1] <= *fhalf.rbegin())
			fhalf.erase(fhalf.find(v[i - k + 1]));
		else
			shalf.erase(shalf.find(v[i - k + 1]));
		adjust();
	}
}
