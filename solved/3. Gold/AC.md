```c++
#include <iostream>
#include <deque>
#include <string>
#include <cstring>
using namespace std;

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	
	deque<string> deq;
	
	int t;
	cin >> t;
	for (int tc = 0; tc < t; tc++)
	{
		bool callErr = false;
		int toggle = 1;
		int x;
		string p;
		string n;
		cin >> p;
		cin >> x;
		cin >> n;
		int from = 1;
		for (int i = 1; i < n.size(); i++)
		{
			if (n[i] == ']')
			{
				deq.push_back(n.substr(from, i - from));
				break;
			}
			if (n[i] == ',')
			{
				deq.push_back(n.substr(from, i - from));
				from = i + 1;
			}				
		}

		for (int i = 0; i < p.size(); i++)
		{
			int arrlen = n.length();
			if ('R' == p[i])
			{
				toggle *= -1;
			}
			else 
			{
				if (deq.empty()) 
				{
					callErr = true;
					break;
				}
				else if (deq[0] == "")
				{
					callErr = true;
					break;
				}

				if (toggle < 0)
				{
					string s = deq.back();
					deq.pop_back();
				}
				else 
				{
					string s = deq.front();
					deq.pop_front();
				}
			}
		}

		if (callErr)
		{
			cout << "error" << "\n";
			deq.clear();
			continue;
		}

		int size = static_cast<int>(deq.size());
		cout << "[";
		if (deq.empty()) 
		{
			cout << "]" << "\n";
			deq.clear();
			continue;
		}
			
		if (toggle < 0)
		{
			for (int i = size - 1; i > 0; i--)
			{
				cout << deq[i] << ",";
			}
			cout << deq[0];
		}
		else
		{
			for (int i = 0; i < size - 1; i++)
			{
				cout << deq[i] << ",";
			}
			cout << deq[size - 1];
		}
		cout << "]" << "\n";
		deq.clear();
	}
}
```
### [5430] AC
1. 문자열 제어 고나리가 핵심이다.
2. 문자열을 제어하기위한 string함수의 용도와 프로퍼티의 이해갖 중요한것 같다.
3. deque의 경우 배열이지만 앞뒤 삽입이 용이하다는 점도 알야야 한다.


 