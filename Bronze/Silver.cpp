#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
using namespace std;

set<string> printed;
void DFS(unordered_map<int, int>& um,
	unordered_map<int, bool>& visited,
	vector<int>& container,
	const int& range)
{
	int size = static_cast<int>(container.size());
	if (size == range)
	{
		string s;
		
		for (int i = 0; i < range; i++)
		{
			s += to_string(um[container[i]]) + " ";
		}
		if (printed.count(s))
			return;
		else
			printed.insert(s);
		cout << s << "\n";
		return;
	}

	for (int i = 0; i < um.size(); i++)
	{
		if (visited[i]) continue;
		container.push_back(i);
		visited[i] = true;
		DFS(um, visited, container, range);
		visited[i] = false;
		container.pop_back();
	}
}

void DFSALL(unordered_map<int, int>& um,
	unordered_map<int, bool>& visited, 
	vector<int>& container,
	const int& range)
{
	for (int i = 0; i < um.size(); i++)
	{
		container.push_back(i);
		visited[i] = true;
		DFS(um, visited, container, range);

		container.pop_back();
		visited[i] = false;
	}

}

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	vector<int> v;

	int t, k;
	cin >> t >> k;
	for (int i = 0; i < t; i++)
	{
		int x;
		cin >> x;
		v.push_back(x);
	}
	for (int i = 0; i < t; i++)
	{
		int comp = v[i];
		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (comp < v[j])
				v[j + 1] = v[j];
			else
				break;
		}
		v[j + 1] = comp;
	}
	unordered_map<int, int> um;
	unordered_map<int, bool> visited;
	vector<int> container;
	for (int i = 0; i < t; i++)
	{
		um.insert({i, v[i]});
		visited.insert({i, false});
	}
	
	DFSALL(um, visited, container, k);

	return 0;
}