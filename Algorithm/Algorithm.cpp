#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> maze;
vector<vector<bool>> discovered;

struct Dir {
	int x;
	int y;
};

void CreateGraph()
{
	maze = vector<vector<int>>(4, vector<int>(4));
	discovered = vector<vector<bool>>(4, vector<bool>(4, false));

	maze = {
		{1, 0, 1, 1, 1, 1},
		{1, 0, 1, 0, 1, 0},
		{1, 0, 1, 0, 1, 1},
		{1, 1, 1, 0, 1, 1},
	};
}

void AStar()
{
	/*00 01 02 03
	10 11 12 13
	20 21 22 23
	30 31 32 33*/

	Dir start = { 2, 2 };
	Dir destination = { 0, 1 };

	vector<Dir> dir = {
		{-1, 0},	// 상
		{0, -1},	// 좌
		{1, 0},		// 하
		{0, 1},		// 우
	};
	priority_queue<Dir> queue;

	while(true)
	{

	}
};

int main()
{
	
}