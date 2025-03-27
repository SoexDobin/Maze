#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
	int n1, n2;

	cin >> n1 >> n2;
	int range = n1 <= n2 ? n2 : n1;
	// 최대 공약수
	// 공통으로 나뉘어 지는 수중에서 가장 큰 수
	int bestDivisor = 1;
	int index = range + 1;
	while (index > 2)
	{
		index--;
		if (n1 % index != 0 || n2 % index != 0)
			continue;
			
		if (bestDivisor < index)
			bestDivisor = index;	
	}
	cout << bestDivisor << endl;

	// 최소 공배수
	// 공통으로 가지는 배수 중에서 가장 작은 수
	int leastMutiple = 1;
	int mul = 0;
	index = 0;
	while (mul <= 100000000)
	{
		index++;
		mul = bestDivisor * index;
		if (mul % n1 != 0 || mul % n2 != 0)
			continue;

		leastMutiple = mul;
		break;
	}
	cout << leastMutiple << endl;

}


