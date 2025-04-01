#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()	
{
	multimap<int, string> mp;
	int size;
	int age;
	string name;

	cin >> size;
	for (int i = 0; i < size; i++)
	{
		cin >> age >> name;
		mp.insert({age, name});
	}

	for (int i = 1; i <= 200; i++)
	{
		for (multimap<int, string>::iterator iter = mp.lower_bound(i); iter != mp.upper_bound(i); iter++)
		{
			cout << iter->first << " " << iter->second << endl;
		}
	}
}