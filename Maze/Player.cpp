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
	//BFS();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
		_board->GenerateMap();
		Init(_board);
		return;
	}
		

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

struct PQNode
{
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }

	int32	f;	// f = g + h;
	int32	g;
	Pos		pos;
};

void Player::AStar()
{
	// 점수 매기기
	// F = G + H
	// F = 최종 점수 (작을 수록 좋은, 경로에 따라 달라짐)
	// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용 (작을 수록 좋음, 경로에 따라 달라짐)
	// H = 목적지에서 얼마나 가까운지 (작을 수록 좋음, 고정)

	Pos start = _pos;
	Pos dest = _board->GetExitPos();

	enum
	{
		// DIR_COUNT = 4, // 직각 이동
		DIR_COUNT = 8, // 대각선 이동
	};

	Pos front[8] = {
		Pos {-1, 0},	// UP
		Pos {0, -1},	// LEFT
		Pos {1, 0},		// DOWN
		Pos {0, 1},		// RIGHT
		Pos {-1, -1},	// UP_LEFT
		Pos {1, -1},	// DOWN_LEFT
		Pos {-1, 1},	// UP_RIGHT
		Pos {1, 1}		// DOWN_RIGHT
	};

	int32 cost[] =
	{
		10,		// UP
		10,		// LEFT
		10,		// DOWN
		10,		// RIGHT
		14,		// UP_LEFT
		14,		// DOWN_LEFT
		14,		// UP_RIGHT
		14		// DOWN_RIGHT
	};

	int32 boardSize = _board->GetSize();

	// ClosedList
	// close[y][x] -> (y, x)에 방문을 했는지 여부
	vector<vector<bool>> 
		closed(boardSize, vector<bool>(boardSize, false));

	// best[y][x] -> 지금까지 (y, x)에 대한 가장 좋은 비용 (적을 수록 좋음)
	vector<vector<int32>> 
		best(boardSize, vector<int32>(boardSize, INT32_MAX));

	// 부모 추적 용도
	map<Pos, Pos> parent;

	// OpenList;
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// 1) 예약(발견) 시스템 구현
	// - 이미 더 좋은 경로를 찾았다면 스킵
	// 2) 뒤늦게 더 좋은 경로가 발견될 수 있음 -> 예외 처리 필수
	// - openList에서 찾아서 제거한다거나
	// - pq에서 pop한 다음에 무시한다거나

	// 초기값
	{
		int32 g = 0;
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		PQNode node = pq.top();
		pq.pop();

		// 동일한 좌표를 여러 경로로 찾아서
		// 더 빠른 경로로 인해서 이미 방문(closed)된 경우 스킵

		// [선택] 
		if (closed[node.pos.y][node.pos.x])
			continue;
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// 방문
		closed[node.pos.y][node.pos.x] = true;

		// 목적지에  도착했으면 바로 종료
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			// 갈 수 있는 지역은 맞는지 확인
			if (CanGo(nextPos) == false)
				continue;
			if (closed[nextPos.y][nextPos.x])
				continue;

			// 비용 계산 
			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			// 다른 경로에서 더 빠른 길을 찾았으면 스킵
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// 예약 진행
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}
	}

	Pos pos = dest;
	_path.clear();
	_pathIndex = 0;

	while (true)
	{
		_path.push_back(pos);

		if (parent[pos] == pos)
			break;

		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());
}
