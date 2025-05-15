#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include <thread>
#include <Windows.h>

// 트리가 한쪽으로 기우는 문제를 해결
// 트리를 합칠 때, 항상 [높이가 낮은 트리를] [높이가 높은 트리] 밑으로
// (Union-By-Rank) 랭크에 의한 합치기 최적화
//class DisjointSet
//{
//public:
//	DisjointSet(int n) : _parent(n), _rank(n, 1)
//	{
//		for (int i = 0; i < n; i++)
//			_parent[i] = i;
//	};
//
//	// 팀 리더 서치
//	int Find(int u)
//	{
//		if (u == _parent[u])
//			return u;
//
//		return _parent[u] = Find(_parent[u]);
//	}
//
//	// u가 v 밑으로
//	void Merge(int u, int v)
//	{
//		u = Find(u);
//		v = Find(v);
//
//		// 같은 팀 이면
//		if (u == v)
//			return;
//
//		if (_rank[u] > _rank[v])
//			::swap(u, v);
//
//		// rank[u] <= rank[v]가 보장됨??
//		_parent[u] = v;
//		if (_rank[u] == _rank[v])
//			_rank[v]++;
//	}
//
//private:
//	vector<int> _parent;
//	vector<int> _rank;
//};
//
//struct Vertex
//{
//
//};
//
//vector<Vertex> vertices;
//vector<vector<int>> adjacent; // 인접 행렬
//
//void CreateGraph()
//{
//	vertices.resize(6);
//	adjacent = vector<vector<int>>(6, vector<int>(6, -1));
//
//	adjacent[0][1] = adjacent[1][0] = 15;
//	adjacent[0][3] = adjacent[3][0] = 35;
//	adjacent[1][2] = adjacent[2][1] = 5;
//	adjacent[1][3] = adjacent[3][1] = 10;
//	adjacent[3][4] = adjacent[4][3] = 5;
//	adjacent[3][5] = adjacent[5][3] = 10;
//	adjacent[5][4] = adjacent[4][5] = 5;
//}
//
//struct CostEdge
//{
//	int cost;
//	int u;
//	int v;
//
//	bool operator<(CostEdge& other)
//	{
//		return cost < other.cost;
//	}
//};
//
//int Kruskal(vector<CostEdge>& selected)
//{
//	int ret = 0;
//	selected.clear();
//
//	// 모든 간선의 관계와 코스트 확인
//	vector<CostEdge> edges;
//	for (int u = 0; u < adjacent.size(); u++)
//	{
//		for (int v = 0; v < adjacent[u].size(); v++)
//		{
//			if(u < v)	// 양방향 그래프이기에 같은 값이면 추가하지 않음
//				continue; 
//
//			int cost = adjacent[u][v];
//			if (cost == -1)
//				continue;
//
//			edges.push_back(CostEdge{ cost, u, v });
//		}
//	}
//	std::sort(edges.begin(), edges.end());
//
//	// 그리디 알고리즘
//
//	DisjointSet sets(vertices.size());
//	for (CostEdge& edge : edges)
//	{
//		if (sets.Find(edge.u) == sets.Find(edge.v))
//			continue;
//
//		sets.Merge(edge.u, edge.v);
//		selected.push_back(edge);
//		ret += edge.cost;
//	}
//
//	return ret;
//}
//
//int main()
//{
//	CreateGraph();
//
//	vector<CostEdge> selected;
//	int cost = Kruskal(selected);
//}

int cache[50][50];
int combination(int n, int r)
{
	// 기저 사례
	if (r == 0 || n == r)
		return 1;
	// 이미 답을 구한 적 있으면 바로 반환
	int& ret = cache[n][r];
	if (ret != -1)
		return ret;

	// 새로 답을 구해서 캐시에 저장
	return ret = combination(n - 1, r - 1) + combination(n - 1, r);
}

int main()
{
	::memset(cache, -1, sizeof(cache));
	__int64 start = GetTickCount64();
	int lotto = combination(45, 6);
	__int64 end = GetTickCount64();
	cout << end - start << "ms" << endl;
}