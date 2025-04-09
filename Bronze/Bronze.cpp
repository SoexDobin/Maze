#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;

const int MAX_NUM = 500000;

int main() 
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	
	unordered_map<int, int> m;
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		int x;
		cin >> x;
		m.find(x);
		
		unordered_map<int, int>::iterator it = m.find(x);
		if (it == m.end())
			m.insert(pair<int, int>{ x , 1 });
		else
			m[x]++;
	}
	vector<int> v;
	cin >> t;
	v.resize(t);
	for (int i = 0; i < t; i++)
	{
		int x;
		cin >> x;
		unordered_map<int, int>::iterator it = m.find(x);
		if (it == m.end())
			v[i] = 0;
		else
			v[i] = it->second;
	}
	for (int i = 0; i < t; i++)
	{
		cout << v[i] << " ";
	}
}