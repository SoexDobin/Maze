#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() 
{
	// 1 white 0 black
	vector<vector<int>> v;
	int x, y;
	cin >> y >> x;
	v.resize(y);
	for (int i = 0; i < y; i++)
	{
		string s;
		cin >> s;
		for (char c : s)
		{
			if (c == 'W')
				v[i].push_back(1);
			else
				v[i].push_back(-1);
		}
	}

	// W 시작일 때 칠하기 개수
	// B 시작일 때 칠하기 개수

	int yPos = 0, xPos = 0;
	int leastCount = INT32_MAX;
	while (true)
	{
		int startWhiteAcc = 0;
		int startBlackAcc = 0;
		int whiteToggle = 1;
		int blackToggle = -1;
		for (int i = yPos; i < yPos + 8; i++)
		{
			for (int j = xPos; j < xPos + 8; j++) 
			{
				if (v[i][j] != whiteToggle)
					startWhiteAcc++;
				
				if (v[i][j] != blackToggle)
					startBlackAcc++;
				
				whiteToggle *= -1;
				blackToggle *= -1;
			}
			whiteToggle *= -1;
			blackToggle *= -1;
		}

		if (leastCount > startWhiteAcc)
			leastCount = startWhiteAcc;
		if (leastCount > startBlackAcc)
			leastCount = startBlackAcc;

		int checkX = xPos + 8;
		int checkY = yPos + 8;
		if (checkX < x)
			xPos++;
		else if (checkY < y)
		{
			yPos++;
			xPos = 0;
		}
		else
			break;
	}

	cout << leastCount << "\n";
}

