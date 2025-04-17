#include <iostream>
using namespace std;

int fibo[41] = {0, 1, };
int zero = 0, one = 0;
int Fibonacci(const int& n)
{
	if (n == 0) 
	{
		zero++;
		return 0;
	}
	else if (n == 1)
	{
		one++;
		return 1;
	}
	if (fibo[n])
		return fibo[n];
	else
		return fibo[n] = Fibonacci(n - 1) + fibo[n - 2];
}


int main() 
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		zero = 0, one = 0;
		int x;
		cin >> x;
		Fibonacci(x);

		if (x == 0)
		{
			cout << 1 << " " << 0 << "\n";
			continue;
		}
		cout << fibo[x - 1] << " " << fibo[x] << "\n";
	}
	
}

