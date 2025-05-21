#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int t;
	vector<int> v(50001, 50000);
	vector<bool> visited(50001, false);
	queue<int> q;
	for (int i = 1; i <= 223; i++)
	{
		v[i * i] = 1;
		visited[i * i] = true;
		q.push(i * i);
	}
	cin >> t;
	while (!q.empty())
	{
		int n = q.front();
		q.pop();
		for (int i = 1; i <= t; i++)
		{
			int next = n + (i * i);
			if (next > 50000) break;
			if (v[next] < v[n] + 1 || visited[next]) continue;
			v[next] = v[n] + 1;
			visited[next] = true;
			q.push(next);
		}
	}
	
	cout << v[t];
	return 0;
}