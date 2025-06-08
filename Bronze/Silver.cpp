#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void DequeSerach(const int& from, const int& to)
{
	deque<pair<int, int>> dq;
	vector<int> bestWeight = vector<int>(100001, INT32_MAX);

	dq.push_back({ 0, from });
	bestWeight[from] = 0;
	while (!dq.empty())
	{
		int nowWeight = dq.front().first;
		int nowPos = dq.front().second;
		dq.pop_front();

		if (nowWeight > bestWeight[nowPos]) continue;

		pair<int, int> back = {nowWeight + 1, nowPos - 1};
		if (back.second >= 0 && back.first < bestWeight[back.second])
		{
			bestWeight[back.second] = back.first;
			dq.push_back(back);
		}
		pair<int, int> next = { nowWeight + 1, nowPos + 1 };
		if (next.second <= 100000 && next.first < bestWeight[next.second])
		{
			bestWeight[next.second] = next.first;
			dq.push_back(next);
		}
		pair<int, int> jump = { nowWeight , nowPos * 2 };
		if (jump.second <= 100000 && jump.first < bestWeight[jump.second])
		{
			bestWeight[jump.second] = jump.first;
			dq.push_front(jump);
		}
	}
	cout << bestWeight[to];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int from, to;
	cin >> from >> to;
	DequeSerach(from, to);
}