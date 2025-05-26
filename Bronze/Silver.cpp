#include <iostream>
#include <vector>
using namespace std;

vector<int> line;
void DFS(vector<vector<int>>& v, const int from, int& acc, const int range, const int t)
{
	if (acc == range)
	{
		line.push_back(from);
		for (int j = 0; j < line.size(); j++)
		{
			cout << line[j] << " ";
		}
		cout << "\n";
		line.pop_back();
		return;
	}
	acc += 1;
	int prevAcc = acc;

	for (int i = 0; i < v[from].size(); i++)
	{	
		line.push_back(from);
		DFS(v, v[from][i], acc, range, t);
		if (!line.empty())
			line.pop_back();
		acc = prevAcc;
	}
}

void DFSALL(vector<vector<int>>& v, const int to, const int range)
{
	int acc = 1;
	
	for (int i = 1; i <= to; i++)
	{
		DFS(v, i, acc, range, to);
		acc = 1;
		line.clear();
	}
}

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int t, k;
	cin >> t >> k;
	vector<vector<int>> v = vector<vector<int>>(t + 1);
	for (int i = 1; i <= t; i++)
	{
		for (int j = i + 1; j <= t; j++)
			v[i].push_back(j);
	}
	DFSALL(v, t, k);
	return 0;
}