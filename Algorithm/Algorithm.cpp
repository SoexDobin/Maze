#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

vector<vector<int>> adjacent; // 인접 행렬
void CreateGraph()
{
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}

void Dijkstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	// 발견된 이동 루트
	list<VertexCost> discovered;
	// here에서 다른 정점 간의 최단 누적 거리
	vector<int> bestAccRoute = vector<int>(6, INT32_MAX);
	// 정점의 이전 정점
	vector<int> parent = vector<int>(6, -1);

	// 기본 시작 정점 등록
	discovered.push_back(VertexCost({ here, 0 }));
	bestAccRoute[here] = here;
	parent[here] = here;

	// 정점 순회
	while (discovered.empty() == false)
	{
		list<VertexCost>::iterator bestVertexCost;
		int bestCost = INT32_MAX;

		// 여기서 해당 정점이 탐색 가능한 길 중 가장 효율적인 루트만 가지고 나옴
		for (list<VertexCost>::iterator it = discovered.begin(); it != discovered.end(); it++)
		{
			if (it->cost < bestCost)
			{
				bestCost = it->cost;
				bestVertexCost = it;
			}
		}

		// 가장 효율좋은 루트의 다음 정점 설정, 현재 루트는 제거
		int cost = bestVertexCost->cost;
		here = bestVertexCost->vertex;
		discovered.erase(bestVertexCost);

		// 이미 코스트가 가져온 코스트 보디 작으면 다음 계산
		if (bestAccRoute[here] < cost)
			continue;

		// 다음 정점에 연결된 정점 간 가중치 등록과 계산
		for (int there = 0; there < 6; there++)
		{
			// 연결된 정점이 없다면 스킵
			if (adjacent[here][there] == -1)
				continue;

			// 만약 there까지의 가중치가 기존이 더 효율적이면 스킵
			int edgeCost = bestAccRoute[here] + adjacent[here][there];
			if (edgeCost >= bestAccRoute[there])
				continue;

			bestAccRoute[there] = edgeCost;

			// 가중치가 더효율적인 정점에서 시작하도록 discovered에 등록 
			discovered.push_back(VertexCost{ there , edgeCost });
			parent[there] = here;
		}
	}
}

int main()
{
	CreateGraph();

	Dijkstra(0);
}
