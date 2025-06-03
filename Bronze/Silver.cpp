#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void GreaterDP(const int& n, const int& k, const vector<int>& w, const vector<int>& v, vector<vector<int>>& dp)
{
	// 각 배낭 최대 무게를 1~k 순으로 비교
	for (int i = 1; i <= k; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (w[j] > i) // j번째 물건의 무게, i현재 배낭의 최대 허용 무게
				dp[j][i] = dp[j - 1][i];
			else if (w[j] <= i)
			{
				dp[j][i] = max(dp[j-1][i - w[j]] + v[j], dp[j-1][i]);
			}
		}
	}
}

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	vector<int> w = vector<int>(101);
	vector<int> v = vector<int>(101);
	vector<vector<int>> dp;
	int n, k;
	cin >> n >> k;

	dp = vector<vector<int>>(101, vector<int>(100001, 0));

	for (int i = 1; i <= n; i++)
	{
		cin >> w[i] >> v[i];
	}

	GreaterDP(n, k, w, v, dp);

	cout << dp[n][k];
}