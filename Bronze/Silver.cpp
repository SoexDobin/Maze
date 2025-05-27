#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> line;
unordered_map<int, bool> visited;
void DFS(vector<vector<int>>& g, const int range, const int here)
{
	int size = static_cast<int>(line.size());
	if (size == range)
	{
		for (int i = 0; i < line.size(); i++)
		{
			cout << line[i] << " ";
		}
		cout << "\n";
		return;
	}


	for (int i = 0; i < g[here].size(); i++)
	{
		int data = g[here][i];
		if (visited[data]) continue;
		line.push_back(data);
		visited[data] = true;
		DFS(g, range, i);
		visited[line.back()] = false;
		line.pop_back();
	}
}

void DFSALL(vector<int>& v, vector<vector<int>>& g, const int to, const int range)
{

	for (int i = 0; i < to; i++)
	{
		line.push_back(v[i]);
		visited[v[i]] = true;
		DFS(g, range, i);
		visited[v[i]] = false;
		line.clear();
	}
}

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int t, k;
	cin >> t >> k;
	vector<int> v;
	vector<vector<int>> g = vector<vector<int>>(t);
	for (int i = 0; i < t; i++)
	{
		int x;
		cin >> x;
		v.push_back(x);
		visited.insert({x, false});
	}
	for (int i = 1; i < v.size(); i++)
	{
		int comp = v[i];
		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (v[j] > comp)
				v[j + 1] = v[j];
			else
				break;
		}
		v[j + 1] = comp;
	}
	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < t; j++)
		{
			g[i].push_back(v[j]);
		}
	}
	DFSALL(v, g, t, k);
	return 0;
}