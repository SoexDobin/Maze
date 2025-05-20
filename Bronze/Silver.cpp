#include <iostream>
#include <vector>
using namespace std;

int t;
vector<int> v;
void dp(const int n)
{
	for (int next : {n + 1, n + 2})
	{
		if (next > t) continue;

		v[next]++;
		dp(next);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> t;
	v = vector<int>(t + 1, 0);
	v[1] += 1;
	v[2] += 2;
	
	for (int i = 3; i <= t; i++)
	{
		v[i] = (v[i - 1] + v[i - 2]) % 10007;
	}

	cout << v[t];
}

