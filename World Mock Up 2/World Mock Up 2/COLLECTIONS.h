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
/*
real quick not to make a function pointer use
return type (*to function) (list of arguments);
*/
//void greg(void(*gregory)(double theGregs));


class tile;
class actor;
class world;
class player;
class object;
class renderer;
class image;
class FileReader;
class counter;
class item;
class inventory;

using namespace std;

#ifndef PI
#define PI 2*tan(4)
#endif

#ifndef ACTOR_VECTOR
#define ACTOR_VECTOR
struct ActorVector
{
        unsigned int x;
        unsigned int y;
};
#endif

#ifndef KLEPTO_CALL_BACKS
#define KLEPTO_CALL_BACKS
typedef void(*genericCallback)(void* arg);
typedef void(*actorCallback)(actor &aCharacter, world *map, player *pCharacter);
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

#ifndef _COLLECTIONS
#define _COLLECTIONS

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

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "libpng16.lib")

#include "UTILITIES.h"
using namespace utilities;

#include "IMAGE.h"
#include "NPCHandler.h"
#include "OBJECT.h"
#include "PLAYER.h"
#include "TILE.h"
#include "FILEREADER.h"
#include "TIMER.h"
#include "WORLD.h"
#include "ITEM.h"
#include "INVENTORY.h"
#include "RENDERER.h"

#endif