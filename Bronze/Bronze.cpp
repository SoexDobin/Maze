#include <iostream>
#include <vector>
using namespace std;

int main() {
   
    vector<vector<int>> v;
    int n;
    int index = 0;

    
    while (true)
    {
        cin >> n;
        if (n == 0) break;

        v.push_back(vector<int>());
        while (n != 0)
        {
            v[index].push_back(n % 10);
            n = n / 10;
        }
        index++;
    }
    
    vector<bool> pelVec = vector<bool>( v.size(), true);
    for (int i = 0; i < v.size(); i++)
    {
        int halfSize = v[i].size() / 2;
        int backIndex = v[i].size() - 1;

        bool pel = true;
        for (int j = 0; j < halfSize; j++)
        {
            if (v[i][j] != v[i][backIndex - j])
                pel = false;
        }
        pelVec[i] = pel;
    }

    for (int i = 0; i < pelVec.size(); i++)
    {
        if (pelVec[i])
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
}

//vector<int> cards;
//vector<vector<vector<bool>>> alreadyDone;
//
//int main()
//{
//	// 카드 양의 정수
//	// n장의 카드중
//	// n[0] + n[1] + n[2] = m장 을 집으세요
//	// m을 넘지 않으면서 가장 유사한 값을 찾아야 한다.
//	unsigned int amount;
//	unsigned int cardCount;
//	cin >> cardCount >> amount;
//
//	int size = cardCount;
//
//	cards = vector<int>(size, 0);
//	alreadyDone = vector<vector<vector<bool>>>(size, vector<vector<bool>>(size, vector<bool>(size, false)));
//	for (int i = 0; i < cardCount; i++)
//	{ 
//		int n;
//		cin >> n;
//
//		if (n < 3 || n > 300000) return 0;
//
//		cards[i] = n;
//	}
//
//	int best = 0;
//	for (int i = 0; i < cards.size(); i++)
//	{
//		for (int j = 0; j < cards.size(); j++)
//		{
//			if (i == j) continue;
//			for (int k = 0; k < cards.size(); k++)
//			{
//				if (alreadyDone[i][j][k]) continue;
//				alreadyDone[i][j][k] = true;
//				if (j == k) continue;
//
//				int compare = cards[i] + cards[j] + cards[k];
//				if (best > compare) continue;
//				if (compare > amount) continue;
//				best = compare;
//			}
//		}
//	}
//	
//	cout << best << endl;
//}

