```c++
#include <iostream>

using namespace std;

void NCounter(const int& n)
{
	int i = 1;
	while(i <= n)
	{
		cout << i++ << "\n";
	}
}

int main()
{
	int n;
	cin >> n;
	if (n < 1 || n > 100000) return 0;

	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	NCounter(n);
}
```
1. ```cin.tie(NULL);``` cout과 cin의 출력 스트림 묶음을 풀어준다. <br> 
    이렇게 하면 스트림에 flush 연산으로 출력 버퍼를 모두 출력하고 비우는 연산을 맨마지막으로 한번만 하게 유도할 수 있다. 
2. ```ios_base::sync_with_stdio(false);```으로 C버전의 stdin/stdout과 버퍼를 분리하여 C++에만 집중할 수 있다.  