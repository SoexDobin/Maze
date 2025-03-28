#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() 
{
	int t;
	int k; // 층수 0시작
	int n; // 호수 1시작
	       // 인수는 k-1층의 n호 까지
	vector<vector<int>> room(1, vector<int>(15));
	queue<int> find;
	cin >> t;
	for (int i = 0; i <= 14; i++)
		room[0][i] = i;

	while (t > 0)
	{
		cin >> k;
		cin >> n;

		if (k >= room.size())
			room.resize(k + 1);
		
		
		for (int i = 1; i <= k; i++)
		{
			if (room[i].size() <= n)
				room[i].resize(n + 1, 0);

			int acc = 0;
			for (int j = 1; j <= n; j++)
			{	
				acc += room[i - 1][j];
				room[i][j] = acc;
			}
		}
		find.push(room[k][n]);
		t--;
	}
	while (find.empty() == false)
	{
		cout << find.front() << "\n";
		find.pop();
	}
}
