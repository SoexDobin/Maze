#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool binary_search(const vector<int>& v, int x)
{
	int low = 0, high = v.size() - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (v[mid] == x) return true;
		if (v[mid] < x) low = mid + 1;
		else high = mid - 1;
	}
	return 0;
}

int main() 
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	vector<int> v;
	int size;
	cin >> size;
	v.resize(size);
	for (int i = 0; i < size; i++)
	{
		int x;
		cin >> x;
		v[i] = x;
	}
	::sort(v.begin(), v.end());
	cin >> size;
	for (int i = 0; i < size; i++)
	{
		int x;
		cin >> x;
		cout << binary_search(v, x) << "\n";
	}
}


