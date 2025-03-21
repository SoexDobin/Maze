#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> adjacent;
vector<bool> discovered;

void CreateGraph()
{
	adjacent = vector<vector<int>>(6);
	discovered = vector<bool>(6, false);

	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);
}

void BFS(int here)
{
	// 누구에 의해 발견 되었는지?
	vector<int> parent(6, -1);
	// 시작점에서 얼만큼 떨어져 있는지?
	vector<int> distance(6, -1);

	queue<int> q;
	q.push(here);
	discovered[here] = true;

	parent[here] = here;
	distance[here] = 0;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		cout << "Visited : " << here << endl;

		for (int there : adjacent[here])
		{
			if (discovered[there])
				continue;

			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;
		}
	}
}

void BFSAll()
{
	for (int i = 0; i < adjacent.size(); i++)
	{
		if (discovered[i])
			continue;

		BFS(i);
	}
}

int main()
{
	CreateGraph();

	BFS(0);
	//BFSAll();
}
