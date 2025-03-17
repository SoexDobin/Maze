#pragma once

class Board;

class Player
{
	enum
	{
		MOVE_TICK = 100
	};

public:
	Player();
	virtual ~Player();

	void Init(Board* board);
	void Update(uint64 deltaTick);
	bool CanGo(Pos pos);

	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }

private:
	Pos _pos = {};
	int32 _dir = DIR_UP;
	Board* _board = nullptr;

	vector<Pos> _path;
	uint32 _pathIndex = 0;
	uint64 _sumTick = 0;
};

