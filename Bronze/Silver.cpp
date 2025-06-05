#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

void Dijkstra(const int& from, const vector<vector<pair<int, int>>>& g, const int& v)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<int> bestWeight = vector<int>(v + 1, INT32_MAX);

	bestWeight[from] = 0;
	pq.push(pair<int, int>(0, from));
	while (!pq.empty())
	{
		int nowVertex = pq.top().second;
		int nowWeight = pq.top().first;
		pq.pop();
		if (nowWeight > bestWeight[nowVertex]) continue;

		for ( pair<int, int> nextVertex : g[nowVertex])
		{
			int nextWeight = nextVertex.second;

			if (bestWeight[nextVertex.first] > nextWeight + nowWeight)
			{
				bestWeight[nextVertex.first] = nextWeight + nowWeight;
				pq.push(pair<int, int>(nextWeight + nowWeight, nextVertex.first));
			}
		}
	}

	for (int i = 1; i <= v; i++)
	{
		int w = bestWeight[i];
		if (w == INT32_MAX)
			cout << "INF" << "\n";
		else
			cout << w << "\n";
	}
}

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	
	int vertex, edge;
	int from;
	cin >> vertex >> edge;
	cin >> from;
	vector<vector<pair<int, int>>> g(vertex + 1);

	for (int i = 0; i < edge; i++)
	{
		int here, there, weight;
		cin >> here >> there >> weight;

		g[here].push_back({there, weight});
	}

	Dijkstra(from, g, vertex);
}