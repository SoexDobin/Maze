#include <iostream>

using namespace std;

void NCounter(const int& n)
{
	int i = 1;
	while(i <= n)
	{
		cout << i++ << "\n";
	}
}

int main()
{
	int n;
	cin >> n;
	if (n < 1 || n > 100000) return 0;

	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	NCounter(n);
}