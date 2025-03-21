#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

Player::Player()
{

}

Player::~Player()
{
	
}

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	BFS();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);

	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = _board->GetExitPos();

	Pos front[4] = {
		Pos {-1, 0},	// UP
		Pos {0, -1},	// LEFT
		Pos {1, 0},		// DOWN
		Pos {0, 1},		// RIGHT
	};

	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;

		if (CanGo(pos + front[newDir]))
		{
			// 오른쪽 방향으로 90도 회전
			_dir = newDir;
			// 앞으로 한 보 전진
			pos += front[_dir];
			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 보 전진
			pos += front[_dir];
			_path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향으로 90도 회전
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}

	stack<Pos> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
		{
			s.push(_path[i]);
		}
	}

	// 목적지 도착
	if (_path.empty() == false)
		s.push(_path.back());

	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	std::reverse(path.begin(), path.end());

	_path = path;
}

void Player::BFS()
{
	// 첫 스타트 지점 등록
	// 상하좌우 탐색
	//		visited 검증
	//		Wall Empty() 검증
	//			다 Ok이면 큐로 다음 탁색로 등록
	//			다 OK이면 visited false로 또 큐로 안들어가게 변경
	//			다 OK이면 추적을 위해 map으로 다음 지점 과 현재지점 key value 등록
	//break 마지막 목표인 dest이면 반복 중지

	// 최적 _path 등록을 위해
	// dest를 시작으로 뒤로 경로를 추적 원점 pos까지
	// _path에 push_back();
	// if 원점에 도달하면 반복 탈출
	Pos pos = _pos;
	Pos dest = _board->GetExitPos();
	Pos front[4] = {
		Pos {-1, 0},	// UP
		Pos {0, -1},	// LEFT
		Pos {1, 0},		// DOWN
		Pos {0, 1},		// RIGHT
	};

	int32 boardSize = _board->GetSize();
	vector<vector<bool>> discoverd(boardSize, vector<bool>(boardSize, false));
	map<Pos, Pos> pastPath;
	queue<Pos> q;

	pastPath.insert({ pos, pos });
	q.push(pos);

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		if (pos == dest) break;

		for (int i = 0; i < 4; i++) 
		{
			Pos nextPath = pos + front[i];

			if (discoverd[nextPath.y][nextPath.x]) continue;
			if (CanGo(nextPath) == false) continue;

			discoverd[nextPath.y][nextPath.x] = true;
			q.push(nextPath);
			pastPath.insert({ nextPath , pos});
		}
	}
	
	_path.clear();

	pos = dest;

	while (true)
	{
		_path.push_back(pos);

		if (pastPath[pos] == pos)
			break;

		pos = pastPath[pos];
	}

	std::reverse(_path.begin(), _path.end());
}
