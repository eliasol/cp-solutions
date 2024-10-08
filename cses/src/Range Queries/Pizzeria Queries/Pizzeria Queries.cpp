#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>
#include <cassert>

template<typename T, typename S, typename Iterator>
class random_access_member_iterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type   = typename Iterator::difference_type;
	using value_type		= T;
	using pointer		   = T*;
	using reference		 = T&;

private:
	Iterator m_it;
	T S::*m_member_ptr;

public:
	random_access_member_iterator() : random_access_member_iterator(nullptr, nullptr) {}
	random_access_member_iterator(Iterator it, T S::*member_ptr) : m_it(it), m_member_ptr(member_ptr) {}

	reference operator*() { return (*m_it).*m_member_ptr; }
	pointer operator->() { return &((*m_it).*m_member_ptr); }
	const reference operator*() const { return (*m_it).*m_member_ptr; }
	const pointer operator->() const { return &((*m_it).*m_member_ptr); }
	random_access_member_iterator& operator++() { ++m_it; return *this; }
	random_access_member_iterator operator++(int) { auto tmp = *this; m_it++; return tmp; }
	random_access_member_iterator& operator--() { --m_it; return *this; }
	random_access_member_iterator operator--(int) { auto tmp = *this; m_it--; return tmp; }
	random_access_member_iterator& operator+=(difference_type n) { m_it += n; return *this; }
	random_access_member_iterator operator+(difference_type n) const { return random_access_member_iterator(m_it + n, m_member_ptr); }
	random_access_member_iterator& operator-=(difference_type n) { m_it -= n; return *this; }
	random_access_member_iterator operator-(difference_type n) const { return random_access_member_iterator(m_it - n, m_member_ptr); }
	bool operator==(const random_access_member_iterator<T, S, Iterator>& p1) const { return m_it == p1.m_it && m_member_ptr == p1.m_member_ptr; }
	bool operator!=(const random_access_member_iterator<T, S, Iterator>& p1) const { return m_it != p1.m_it || m_member_ptr != p1.m_member_ptr; }
	difference_type operator-(const random_access_member_iterator<T,S,Iterator>& p1) const { return m_it - p1.m_it; }
};

template<typename T, typename S, typename Iterator>
random_access_member_iterator<T, S, Iterator> operator+(typename random_access_member_iterator<T,S,Iterator>::difference_type p1, const random_access_member_iterator<T,S,Iterator>& p2)
{
	auto tmp = p2;
	p2 += p1;
	return tmp;
}

class segment_tree
{
private:
	int real_size;
	std::vector<std::pair<int, int>> data;

	int compute_size(int size)
	{
		int res = 1;
		while (res < size)
			res *= 2;
		return res;
	}

	int m_query(int a, int b, int v, int l, int r, int std::pair<int, int>::*k)
	{
		if (a >= r || b <= l)
			return std::numeric_limits<int>::max();
		if (a <= l && b >= r)
			return data[v].*k;
		return std::min(
			m_query(a, b, 2 * v, l, (l + r) / 2, k),
			m_query(a, b, 2 * v + 1, (l + r) / 2, r, k)
		);
	}

	void m_set(int x, int y, int v, int l, int r)
	{
		if (x < l || x >= r)
			return;
		if (l + 1 == r)
		{
			data[v] = { y + x, y + real_size - x - 1 };
			return;
		}
		m_set(x, y, 2 * v, l, (l + r) / 2);
		m_set(x, y, 2 * v + 1, (l + r) / 2, r);
		data[v] = {
			std::min(data[2 * v].first, data[2 * v + 1].first),
			std::min(data[2 * v].second, data[2 * v + 1].second)
		};
	}

public:
	template<typename Iterator>
	segment_tree(Iterator begin, Iterator end) : real_size(compute_size(end - begin)), data(2 * real_size, { std::numeric_limits<int>::max() - real_size + 1, std::numeric_limits<int>::max() - real_size + 1 })
	{
		std::copy(begin, end, random_access_member_iterator(data.begin(), &std::pair<int, int>::first) + real_size);
		std::copy(begin, end, random_access_member_iterator(data.begin(), &std::pair<int, int>::second) + real_size);

		for (int i = 0; i < real_size; ++i)
			data[real_size + i].first += i,
			data[real_size + i].second += real_size - i - 1;
		for (int i = real_size - 1; i > 0; --i)
			data[i] = {
				std::min(data[2 * i].first, data[2 * i + 1].first),
				std::min(data[2 * i].second, data[2 * i + 1].second)
			};
	}

	int query(int x)
	{
		return std::min(
			m_query(0, x, 1, 0, real_size, &std::pair<int, int>::second) - (real_size - x - 1),
			m_query(x, real_size, 1, 0, real_size, &std::pair<int, int>::first) - x
		);
	}

	void set(int x, int v) { m_set(x, v, 1, 0, real_size); }
};

int main()
{
	int n, q;
	std::cin >> n >> q;

	std::vector<int> v(n);
	for (int& i : v)
		std::cin >> i;

	segment_tree st(v.begin(), v.end());

	while (q--)
	{
		int i;
		std::cin >> i;

		if (i == 1)
		{
			int a, b;
			std::cin >> a >> b;
			st.set(a - 1, b);
		}
		else
		{
			int a;
			std::cin >> a;
			std::cout << st.query(a - 1) << '\n';
		}
	}
}
