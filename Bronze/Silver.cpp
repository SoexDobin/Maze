#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//void Dijkstra(const int& from, const int& to)
//{
//	deque<int> dq;
//	vector<int> v = vector<int>(100001, INT32_MAX);
//	v[from] = 0;
//	dq.push_back(from);
//
//	while (!dq.empty())
//	{
//		int nowPos = dq.front();
//		dq.pop_front();
//
//		int backPos = nowPos - 1;
//		int nextPos = nowPos + 1;
//		int teleportPos = nowPos * 2;
//
//		int nextSearch = v[nowPos] + 1;
//		if (backPos > -1 && v[backPos] > nextSearch)
//		{
//			v[backPos] = nextSearch;
//			dq.push_back(backPos);
//		}
//		if (nextPos < 100001 && v[nextPos] > nextSearch)
//		{
//			v[nextPos] = nextSearch;
//			dq.push_back(nextPos);
//		}
//		if (teleportPos < 100001 && v[teleportPos] > v[nowPos])
//		{
//			v[teleportPos] = v[nowPos];
//			dq.push_front(teleportPos);
//		}
//	}
//	cout << v[to];
//}
//
//int main()
//{
//	cin.tie(nullptr);
//	ios_base::sync_with_stdio(false);
//	
//	int from, to;
//	cin >> from >> to;
//
//	Dijkstra(from, to);
//}

vector<int> Dijkstra(const int& start, const vector<vector<pair<int, int>>>& g, const int& vertex)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<int> bestWeight = vector<int>(vertex + 1, INT32_MAX);

	pq.push({ 0, start });
	bestWeight[start] = 0;
	while (!pq.empty())
	{
		int nowWeight = pq.top().first;
		int nowPos = pq.top().second;
		pq.pop();

		if (bestWeight[nowPos] < nowWeight) continue;

		for (int i = 0; i < g[nowPos].size(); i++)
		{
			int nextPos = g[nowPos][i].first;
			int edgeWeight = g[nowPos][i].second;

			int accWeight = nowWeight + edgeWeight;
			if (bestWeight[nextPos] > accWeight)
			{
				bestWeight[nextPos] = accWeight;
				pq.push({ accWeight, nextPos });
			}
		}
	}
	
	return bestWeight;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int vertex, edge;
	cin >> vertex >> edge;
	vector<vector<pair<int, int>>> g = vector<vector<pair<int, int>>>(vertex + 1);
	for (int i = 0; i < edge; i++)
	{
		int from, to, w;
		cin >> from >> to >> w;
		g[from].push_back({ to, w });
		g[to].push_back({ from, w });
	}
	int vis1, vis2;
	cin >> vis1 >> vis2;
	vector<int> startWeights = Dijkstra(1, g, vertex);
	vector<int> vis1Weights = Dijkstra(vis1, g, vertex);
	vector<int> vis2Weights = Dijkstra(vis2, g, vertex);

	int compWeight1 = startWeights[vis1] + vis1Weights[vis2] + vis2Weights[vertex];
	int compWeight2 = startWeights[vis2] + vis2Weights[vis1] + vis1Weights[vertex];
	int anw = min(compWeight1, compWeight2);
	if (anw >= INT32_MAX || startWeights[vis1] == INT32_MAX || vis1Weights[vis2] == INT32_MAX || vis2Weights[vertex] == INT32_MAX)
		cout << -1;
	else
		cout << anw;
}