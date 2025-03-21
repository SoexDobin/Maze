
//using namespace std;
//
//struct Vertex{ int data; };
//
//vector<Vertex> vertices;
//vector<vector<int>> adjacent;
//vector<bool> visited;
//
//void CreateGraph()
//{
//	vertices.resize(6);
//	adjacent = vector<vector<int>>(6);
//
//	// 인접 리스트
//	/*adjacent[0].push_back(1); adjacent[0].push_back(3);
//	adjacent[1].push_back(0); adjacent[1].push_back(2); adjacent[1].push_back(3);
//	adjacent[3].push_back(4); 
//	adjacent[5].push_back(4);*/
//
//	// 인접 행렬
//	adjacent = vector<vector<int>>
//	{
//		{ 0, 1, 0, 1, 0, 0 },
//		{ 1, 0, 1, 1, 0, 0 },
//		{ 0, 0, 0, 0, 0, 0 },
//		{ 0, 0, 0, 0, 1, 0 },
//		{ 0, 0, 0, 0, 0, 0 },
//		{ 0, 0, 0, 0, 1, 0 },
//	};
//};
//
///*
//DFS(0)
//- DFS(1)
//-- DFS(0) visited
//-- DFS(2)
//-- DFS(3)
//--- DFS(4)
//
//*/
//void DFS(int here)
//{
//	// 방문
//	visited[here] = true;
//	cout << "Visited : " << here << endl;
//
//	// 인접 리스트 버전
//	// 모든 인접 정점을 순회한다
//	/*for (int i = 0; i < adjacent[here].size(); i++)
//	{
//		int there = adjacent[here][i];
//
//		if (visted[there] == false)
//			DFS(there);
//	}*/
//
//	// 인접 행렬 버전
//	// 모든 인접 정점을 순회한다
//	for (int there = 0; there < 6; there++)
//	{
//		if (adjacent[here][there] == 0)
//			continue;
//
//		// 아직 방문하지 않은 곳이 있으면 방문한다
//		if (visited[there] == false)
//			DFS(there);
//	}
//}
//
//void DFSAll(int root)
//{
//	visited = vector<bool>(6, false);
//
//	for (int i = 0; i < root; i++)
//	{
//		if (visited[i] == false)
//			DFS(i);
//		cout << endl;
//	}
//		
//}

//#include <iostream>
//#include <vector>
//#include <map>
//
//using namespace std;
//
//vector<vector<int>> route;
//vector<bool> visited;
//
//void CreateGraph()
//{
//	route.resize(7);
//	
//	route[0].push_back(1); route[0].push_back(2);
//	route[1].push_back(2); route[1].push_back(3); route[1].push_back(4);
//	route[2].push_back(1); route[2].push_back(5); route[2].push_back(6);
//	route[3].push_back(1); route[3].push_back(4);
//	route[4].push_back(1); route[4].push_back(3);
//	route[5].push_back(2); route[5].push_back(6);
//	route[6].push_back(2); route[6].push_back(5);
//
//	visited = vector<bool>(route.size(), false);
//}
//
//void DFS(int here)
//{
//	visited[here] = true;
//	cout << "Visited " << here << " | Data is : " << here + 1 << endl;
//
//	for (int i = 0; i < route[here].size(); i++)
//	{
//		int there = route[here][i];
//
//		if (visited[there] == false)
//		{
//			DFS(there);
//		}
//	}
//}
//
//void DFSAll()
//{
//	for (int i = 0; i < route.size(); i++)
//	{
//		if (visited[i] == false)
//			DFS(i);
//	}
//}
//
//int main()
//{
//	// 이미 들어간 곳은 재귀로 경로를 추적하지 않음
//	// 들어가면 그곳은 방문 체크를 해야함
//	// 모든 경로에서 시범을 보여야 한다.
//	CreateGraph();
//
//	DFS(0);
//	//DFSAll();
//}

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adjacent;
vector<bool> visited;

void CreateGraph(int size) {

	adjacent.resize(size);
	visited = vector<bool>(size, false);

	adjacent[0].push_back(1); 
	adjacent[0].push_back(3); 
	adjacent[1].push_back(0); 
	adjacent[1].push_back(2); 
	adjacent[1].push_back(3);
	adjacent[3].push_back(4); 
	adjacent[5].push_back(4);
}

void DFS(int here)
{
	visited[here] = true;

	cout << "Visited : " << here << endl;

	for (int i = 0; i < adjacent[here].size(); i++)
	{
		int there = adjacent[here][i];

		if (visited[there] == false) 
		{
			DFS(there);
			// DFS(here); // 양방향일 경우 기존 시퀀스도 동일하게 이루어져야 한다.
		}
	}
}

void DFSAll()
{
	for (int i = 0; i < adjacent.size(); i++)
	{
		if (visited[i] == false)
			DFS(i);
	}
}

int main()
{
	CreateGraph(6);
	DFSAll();
}

