#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void DFS(vector<vector<int>>& v, vector<bool>& visited, const int& next, const int& range)
{
	if (visited[next]) return;
	cout << next << " ";
	
	visited[next] = true;

	for (int i = 1; i < range; i++)
	{
		if (v[next][i] != 0)
			DFS(v, visited, v[next][i], range);
	}
}

void BFS(vector<vector<int>>& v, vector<bool>& visited, const int& next, const int& range)
{
	cout << "\n" << next << " ";
	if (visited[next]) return;
	queue<int> q;
	
	visited[next] = true;
	q.push(next);
	while (!q.empty())
	{
		for (int i = 1; i < range; i++)
		{
			if (visited[v[q.front()][i]]) continue;
			if (v[q.front()][i] != 0)
			{
				visited[v[q.front()][i]] = true;
				cout << v[q.front()][i] << " ";
				q.push(v[q.front()][i]);
			}
		}
		q.pop();
	}
}

int main() 
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int n, m, t;
	cin >> n >> m >> t;
	vector<vector<int>> v(n + 1, vector<int>(n + 1, 0));
	vector<bool> visited(n + 1, true);
	visited[t] = false;
	for (int i = 1; i <= m; i++)
	{
		int from, to;
		cin >> from >> to;
		v[from][to] = to;
		v[to][from] = from;
		visited[from] = false;
		visited[to] = false;
	}

	vector<vector<int>> temp = v;
	vector<bool> visitedTemp = visited;

	DFS(v, visited, t, n + 1);
	BFS(temp, visitedTemp, t, n + 1);
}