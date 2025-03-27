#include <iostream>
#include <vector>
using namespace std;

int main() {
	
	int num;
	int count = 0;
	cin >> num;
	int number = 1;
	for (int i = 0; i <= num; i++)
	{
		number += 6 * i;
		if (num == 1) 
		{
			count = 1; 
			break;
		}
		if (number >= num)
		{
			count = i + 1;
			break;
		}
	}
	
	cout << count << endl;
}


