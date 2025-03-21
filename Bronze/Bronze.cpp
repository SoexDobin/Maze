#include <iostream>
#include <string>
using namespace std;

int main()
{
	char s[1001];
	int i;
	
	cin >> s;
	cin >> i;

	for (int j = 0; j < i; j++) {
		if (j == i - 1)
			cout << s[j] << endl;
	}
}