#include <iostream>
using namespace std;

int main()
{
	int* num;
	int bestNum = INT32_MIN;
	int minimunNum = INT32_MAX;
	int size;

	cin >> size;
	num = new int[size];
	for (int i = 0; i < size; i++)
	{
		int input;

		cin >> input;
		num[i] = input;
	}

	for (int i = 0; i < size; i++)
	{
		if (bestNum < num[i])
			bestNum = num[i];
		if (minimunNum > num[i])
			minimunNum = num[i];
	}
	
	cout << minimunNum << " " << bestNum << endl;
}