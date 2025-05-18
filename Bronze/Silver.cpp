#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	vector<int> dp(1000000 + 1, INT32_MAX);
	queue<int> q;
	dp[1] = 0;
	cin >> t;
	q.push(1);
	
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		int mulThree = cur * 3;
		int mulTwo = cur * 2;
		int addOne = cur + 1;
		
		if (mulThree <= t && dp[mulThree] > dp[cur] + 1)
		{
			dp[mulThree] = dp[cur] + 1; 
			q.push(mulThree);
		}
		if (mulTwo <= t && dp[mulTwo] > dp[cur] + 1)
		{
			dp[mulTwo] = dp[cur] + 1; 
			q.push(mulTwo);
		}
		if (addOne <= t && dp[addOne] > dp[cur] + 1)
		{
			dp[addOne] = dp[cur] + 1; 
			q.push(addOne);
		}
	}

	cout << dp[t] << '\n';
	return 0;
}

