#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

int main()
{
	vector<string> s;
	int size;
	
	cin >> size;
	s.resize(size);
	for (int i = 0; i < size; i++) 
	{
		cin >> s[i];
	}
	
	for (int i = 1; i < size; i++)
	{
		string cmpstr = s[i];

		int j;
		for (j = i - 1; j >= 0; j--)
		{
				
			// 현재 단어가 더 짧으면
			if (s[j].size() > cmpstr.size())
				s[j + 1] = s[j];
			else if (s[j].size() == cmpstr.size())
			{
				int k = strcmp(&s[j].front(), &cmpstr.front());

				if (k > 0)
					s[j + 1] = s[j];
				else
					break;
			}
			else
				break;
		}
		s[j + 1] = cmpstr;
	}
	
	string prev = "";
	for (int i = 0; i < size; i++)
	{
		if (s[i] == prev) continue;
		cout << s[i] << endl;
		prev = s[i];
	}
}