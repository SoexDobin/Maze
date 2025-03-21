#pragma once
#include "types.h"
#include "ConsoleHelper.h"
#include "Player.h"

enum
{
	BOARD_MAX_SIZE = 100,
};

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL,
};

class Board
{
public:
	Board();
	virtual ~Board();

	void			Init(int32 size, Player* player);
	void			Render();
	void			GenerateMap();
	TileType		GetTileType(Pos pos);
	ConsoleColor	GetTileColor(Pos pos);

	Pos				GetEnterPos() { return Pos{ 1,1 }; };
	Pos				GetExitPos() { return Pos{ _size - 2 ,_size - 2 }; };
	int32			GetSize() { return _size; };

private:
	TileType		_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	int32			_size = 0;
	Player*			_player = nullptr;
};

