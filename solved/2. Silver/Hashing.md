```c++
#include <iostream>
#include <map>
#include <string>
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

	unsigned long long mul = 1;                      // 이 부분이 중요!
	for (int j = 0; j < i; j++)
	{
		mul = (mul * 31) % M;
	}
	unsigned long long acc = (value * mul) % M;
	acc = (acc + Factorial(m, i + 1, s)) % M;

	return acc;
}

```
### [15829] Hashing
1. 모듈러 연산(나머지 연산)이라는 키워드를 가지는 문제이다.
2. 제곱수를 가지는 ```mul```이 메모리가 표현 가능한 최대 수 이상을 표현할 수도 있다.
3. 때문에 M 모듈러 변수를 나눈 나머지 값을 대입하여 오버 플로우 방지가 핵심이다. 