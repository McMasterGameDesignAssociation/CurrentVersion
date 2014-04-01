#ifndef SYSTEM_COLLECTIONS
#define SYSTEM_COLLECTIONS

using namespace std;
//This is for enabling memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef PI
#define PI 2*tan(4)
#endif

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

inline direction operator ++(direction &rhs)
{
	switch(rhs)
	{
		case Up: 
			rhs = Left;
			return Left;
		case Left: 
			rhs = Down;
			return Down;
		case Down: 
			rhs = Right;
			return Right;
		default: 
			rhs = Up;
			return Up;
	}
}


inline direction operator--(direction &rhs)
{
	switch(rhs)
	{
	case Up:
		rhs = Right;
		return Right;
	case Right: 
		rhs = Down;
		return Down;
	case Down: 
		rhs = Left;
		return Left;
	default: 
		rhs = Up;
		return Up;
	}
}
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <png.h>
#include <queue>
#include <math.h>
//Call windows.h only if the system is a windows system
//Else include unistd.h for unix compatibility
#if (defined(_WIN32) || defined (_WIN64))
	#include <Windows.h>
#else
	#inlcude <unistd.h>
#endif

#include "ITEM.h"
#include "INVENTORY.h"
#include "INDICATOR.h"

#endif