#include <iostream>
#include <map>
#include <string>
#include <cmath>
using namespace std;

const int M = 1234567891;
unsigned long long Factorial(map<char, int> m, int f, string s);

int main() 
{
	int n;
	string s;
	cin >> n;
	cin >> s;
	map<char, int> m;
	
	for (int i = 1; i < 27; i++)
	{
		m.insert({(96 + i), i});
	}

	cout << Factorial(m, 0, s) % M << endl;
}

unsigned long long Factorial(map<char, int> m, int i, string s)
{
	
	if (s == "\0") return 0;
	const char c = s.front();
	s = s.substr(1);
	int value = m.find(c)->second;

	unsigned long long mul = 1;
	for (int j = 0; j < i; j++)
	{
		mul = (mul * 31) % M;
	}
	unsigned long long acc = (value * mul) % M;
	acc = (acc + Factorial(m, i + 1, s)) % M;

	return acc;
}
