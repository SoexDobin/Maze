#include <iostream>
using namespace std;

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int tempA;
	int tempB;

	while (cin >> tempA >> tempB)
	{
		cout << tempA + tempB << endl;
	}

	return 0;
}