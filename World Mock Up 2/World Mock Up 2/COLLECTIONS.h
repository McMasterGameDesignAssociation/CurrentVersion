/*
COPYRIGHT BENJAMIN ISHERWOOD 25/02/2014
THIS SOFTWARE IS INTENDED FOR OPEN SOURCE USE, REDISTRIBUTION
IS ENCOURAGE

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
OTHER DEALINGS IN THE SOFTWARE.
*/
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

//#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
//#pragma comment(lib, "glew32.lib")

using namespace std;

#include "NPCHandler.h"
#include "OBJECT.h"
#include "PLAYER.h"
#include "TILE.h"
#include "FILEREADER.h"
#include "WORLD.h"

#include "RENDERER.h"

#include "TIMER.h"

#endif