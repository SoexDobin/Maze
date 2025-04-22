#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(vector<vector<int>>& v, queue<pair<int, int>>& q)
{
	int sizeY = static_cast<int>(v.size());
	int sizeX = static_cast<int>(v[0].size());
	pair<int, int> dir[4] = {
		{-1, 0},
		{0, 1},
		{1, 0},
		{0, -1},
	};

	while (!q.empty())
	{
		pair<int, int> pos = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int y = pos.first + dir[i].first;
			int x = pos.second + dir[i].second;

			if (y == sizeY || y < 0 || x == sizeX || x < 0) 
				continue;

			if (v[y][x] == 1)
			{
				q.push(pair<int, int>{y, x});
				v[y][x] += v[pos.first][pos.second];
			}
		}
	}
}

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int x, y;
	cin >> y >> x;
	queue<pair<int, int>> q;
	vector<vector<int>> v;
	v.resize(y);

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			int n;
			cin >> n;
			v[i].push_back(n);
			if (n == 2)
				q.push(pair<int, int>{i, j});
		}
	}
	
	BFS(v, q);
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			int n = v[i][j];
			if (n == 0)
				cout << n << " ";
			else if (n == 1) 
				cout << -1 << " ";
			else
				cout << n - 2 << " ";
		}
		cout << "\n";
	}
}

