#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define init_io() cin.sync_with_stdio(0); cin.tie(0); cout.sync_with_stdio(0); cout.tie(0)

#define FILE_IO_LOCAL 1
#define FILE_IO_JUDGE 1

#if FILE_IO_LOCAL && !defined(EVAL) || FILE_IO_JUDGE && defined(EVAL)
ifstream fin("input.txt");
ofstream fout("output.txt");
#define cin fin
#define cout fout
#endif

struct node
{
	bool change = 0;
	string name;
	unordered_map<string,node*> children;
};

vector<node> v(1e6);
int alloc_i = 0;
node* alloc() { assert(alloc_i < v.size()); return &v[alloc_i++]; }

int n;
node root;

void dfs(node *nd)
{
	if (nd->children.empty()) return;
	nd->change = 1;
	for (auto &i : nd->children)
	{
		dfs(i.second);
		nd->change = nd->change && i.second->change;
	}
}

void print(node* nd, string& prefix)
{
	if (nd->change) cout << prefix << nd->name << endl;
	else if (!nd->children.empty())
	{
		prefix += nd->name + "/";
		for (auto &i : nd->children) print(i.second,prefix);
		prefix.erase(prefix.end()-nd->name.length()-1, prefix.end());
	}
}

int main()
{
	init_io();

	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		int c; cin >> c;
		string str; cin >> str;
		string buff = "";
		node *curr = &root;
		for (int i = 1; i <= str.length(); ++i)
		{
			if (str[i] == '/' || i == str.length())
			{
				if (curr->children.count(buff) > 0) curr = curr->children[buff];
				else
				{
					node* nd = alloc();
					nd->change = i == str.length() && c;
					nd->name = buff;
					auto ans = curr->children.emplace(buff,nd).first;
					curr = ans->second;
				}
				buff.clear();
			}
			else buff += str[i];
		}
	}

	dfs(&root);

	string s;

	if (root.change) cout << "/" << "\n";
	else print(&root,s);

	return 0;
}
