#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int size;
	int* arr;

	cin >> size;
	arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}


	int primeIndex = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == 1) continue;

		bool isPrime = true;
		int range = static_cast<int>(sqrt(arr[i]) + 1);
		for (int j = 2; j < range; j++)
		{
			int remain = arr[i] % j;
			if (remain == 0)
				isPrime = false;
		}

		if (isPrime)
			primeIndex++;
	}
	
	cout << primeIndex << endl;
	delete[] arr;
}