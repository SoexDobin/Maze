#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include "types.h"

using namespace std;

enum Dif
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4,
};

struct Pos
{
	bool operator==(Pos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator!=(Pos& other)
	{
		return !(*this == other);
	}

	Pos operator+(Pos& other)
	{
		Pos ret;
		ret.y = y + other.y;
		ret.x = x + other.x;
		return ret;
	}

	Pos& operator+=(Pos& other)
	{
		y += other.y;
		x += other.x;
		return *this;
	}

	bool operator<(const Pos& other) const
	{
		if (y != other.y)
			return y < other.y;
		return x < other.x;
	}

	int32 y = 0;
	int32 x = 0;
};