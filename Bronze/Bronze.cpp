#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	int t;
	int* sizeBox;
	string s;
	vector<string> p;
	vector<string> sv;

	cin >> t;
	sv.resize(t);
	sizeBox = new int[t];
	for (int i = 0; i < t; i++)
	{
		cin >> sizeBox[i] >> s;
		sv[i] = s;
	}
	
	p.resize(1000);
	for (int i = 0; i < t; i++)
	{
		int index = 0;
		for (int j = 0; j < sv[i].size(); j++)
		{
			index += sizeBox[i];
			for (int k = 0; k < sizeBox[i]; k++)
			{
				p[i] += sv[i][j];
			}
		}
	}

	for (int i = 0; i < t; i++)
		cout << p[i] << endl;

	delete[] sizeBox;
}