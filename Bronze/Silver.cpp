#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
using namespace std;

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	
	unordered_map<int, int> m;

	int n, length;
	string s;
	cin >> n;
	cin >> length;
	cin >> s;

	string p;
	for (int i = 0; i < n; i++)
	{
		p.append("IO");
	}
	p.append(1, 'I');

	int acc = 0;
	int idx = 0;
	while (true)
	{
		if (s[idx] == 'O')
		{
			idx++;
			continue;
		}

		int to = (n * 2) + 1;
		if (idx + to > length) break;

		string comp = s.substr(idx, to);
		int isSame = strcmp(comp.c_str(), p.c_str());

		if (isSame == 0)
		{
			idx += 2;
			acc++;
		}
		else
			idx++;
	}
	cout << acc;
}

