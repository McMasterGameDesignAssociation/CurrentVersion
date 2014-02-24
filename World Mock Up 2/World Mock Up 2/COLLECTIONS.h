#pragma once

#ifndef _ITEM_TYPES
#define _ITEM_TYPES

static enum itemType{clothing, electronics, games, food};

#endif

#ifndef _COUNTER_OPTIONS
#define _COUNTER_OPTIONS

static enum countChoice{reset, inc};

#endif

#ifndef _DIRECTION
#define _DIRECTION

static enum direction{Up, UpLeft, Left, DownLeft, Down, DownRight, Right, UpRight};

inline direction operator ++(const direction rhs)
{
	switch(rhs)
	{
		case Up: return Left;
		case Left: return Down;
		case Down: return Right;
		default: return Up;
	}
}

inline direction operator--(const direction rhs)
{
	switch(rhs)
	{
	case Up: return Right;
	case Right: return Down;
	case Down: return Left;
	default: return Up;
	}
}
#endif

#ifndef _COLLECTIONS
#define _COLLECTIONS

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#include "NPCHandler.h"
#include "OBJECT.h"
#include "PLAYER.h"
#include "TILE.h"
#include "WORLD.h"

#include "RENDERER.h"

#include "TIMER.h"

#endif