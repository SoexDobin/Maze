```c++
#include <iostream>
using namespace std;

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int tempA;
	int tempB;

    // while (!(cin >> tempA >> tempB).eof())
	while (cin >> tempA >> tempB)
	{
		cout << tempA + tempB << endl;
	}

	return 0;
}
```
1. 입력이 더 이상 들어오지 않으면 윈도우 기준```Ctrl + Z``` 또는 EOF(End Of File)로 프로그램이 종료 된다.
2. EOF는 파일이나 입력 스트림의 끝을 나타내는 신호입니다. 즉, 더 이상 읽을 데이터가 없음을 나타내며 bool 값을 반환한다.