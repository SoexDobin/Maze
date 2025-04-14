```c++
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
```
### [1260] DFS와 BFS
1. 배열 받을 때는 이중일 경우 ```push_back()```함수를 사용할 것 
2. 넓이 우선 탐색과 깊이 우선 탐색도 중요하지만 본 시점에서 간선이 하나도 존재하지 않을때   
시작점 출력을 하지 않아 틀렸었음
```
정답
3 1 1 // 정점 개수 / 간선 개수 / 시작 노드
2 3   // 2 3 간선
1     // 간선 없으니 시작점 1
1     // 간선 없으니 시작점 1

오류 시점 때 콘솔
3 1 1 // 정점 개수 / 간선 개수 / 시작 노드
2 3   // 2 3 간선
      // 출력 안함
      // 출력 안함
```
 