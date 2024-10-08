#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <functional>

std::mt19937 rng(42069);
std::uniform_int_distribution<int> priority_dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

struct treap
{
	char c;
	int priority;
	bool flip = false;

	treap* l = nullptr;
	treap* r = nullptr;
	int sz = 1;

	treap(char c) : c(c), priority(priority_dist(rng)) {}
	treap() : treap('\0') {}
};

inline int size(const treap* x) { return x ? x->sz : 0; }

inline void push(treap* x)
{
	if (!x->flip)
		return;
	if (x->l)
		x->l->flip = !x->l->flip;
	if (x->r)
		x->r->flip = !x->r->flip;
	std::swap(x->l, x->r);
	x->flip = false;
}

void split(treap* x, int k, treap*& l, treap*& r)
{
	l = nullptr, r = nullptr;
	if (!x)
		return;
	push(x);
	if (size(x->l) < k)
		split(x->r, k - size(x->l) - 1, x->r, r), l = x;
	else
		split(x->l, k, l, x->l), r = x;

	if (l)
		l->sz = size(l->l) + size(l->r) + 1;
	if (r)
		r->sz = size(r->l) + size(r->r) + 1;
}

void merge(treap* l, treap* r, treap*& res)
{
	if (!l || !r)
	{
		res = l ? l : r;
		return;
	}

	push(l);
	push(r);

	if (l->priority > r->priority)
		merge(l->r, r, l->r), res = l;
	else
		merge(l, r->l, r->l), res = r;

	res->sz = size(res->l) + size(res->r) + 1;
}

template<typename Iterator>
treap* treapify(Iterator begin, Iterator end)
{
	if (begin == end)
		return nullptr;
	Iterator m = begin + (end - begin) / 2;
	m->l = treapify(begin, m);
	m->r = treapify(std::next(m), end);
	m->sz = size(m->l) + size(m->r) + 1;

	if (m->l && m->priority < m->l->priority)
		std::swap(m->priority, m->l->priority);
	if (m->r && m->priority < m->r->priority)
		std::swap(m->priority, m->r->priority);
	return &*m;
}

void printTreap(treap* x)
{
	if (!x)
		return;
	push(x);
	printTreap(x->l);
	std::cout << x->c;
	printTreap(x->r);
}

int main()
{
	int n, m;
	std::cin >> n >> m;

	std::vector<treap> v(n);

	for (treap& i : v)
		std::cin >> i.c;
	treap* root = treapify(v.begin(), v.end());

	while (m--)
	{
		int a, b;
		std::cin >> a >> b;

		treap *sus1, *sus2, *sus3;
		split(root, a - 1, sus1, sus2);
		split(sus2, b - a + 1, sus2, sus3);
		sus2->flip = !sus2->flip;

		merge(sus1, sus2, root);
		merge(root, sus3, root);
	}

	printTreap(root);
	std::cout << std::endl;
}
