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
class sprite;
class entity;
class gamepiece;
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

#ifndef _COLLECTIONS
#define _COLLECTIONS

/*
real quick not to make a function pointer use
return type (*to function) (list of arguments);
*/
#ifndef KLEPTO_CALL_BACKS
#define KLEPTO_CALL_BACKS
typedef void(*genericCallback)(void* arg);
typedef void(*actorCallback)(actor &aCharacter, world *map, player *pCharacter);
#endif

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "libpng16.lib")

#include "SYSTEMCOLLECTIONS.h"
#include "UTILITIES.h"
using namespace utilities;

#include "SPRITE.h"
#include "ENTITIES.h"
#include "GAMEPIECES.h"
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