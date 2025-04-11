#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	int n, k;
	vector<int> v;
	cin >> n >> k;
	v.resize(n);
	for (int i = 0; i < n; i++)
	{
		v[i] = i + 1;
	}
	int acc = k - 1;
	int prev = 0;
	int size = n;
	vector<int>::iterator it = v.begin() + acc + prev;
	vector<int> v2;

	while (true)
	{
		v2.push_back(*it);
		v.erase(it);

		size--;
		if (size == 0) break;

		prev = acc - 1;
		acc = (k + prev) % (size);
		it = v.begin() + acc;
	}

	vector<int>::iterator yo;
	cout << "<";
	for (yo = v2.begin(); yo != v2.end() - 1; yo++)
	{
		cout << *yo << ", ";
	}
	cout << *(v2.end() - 1) <<">";
}