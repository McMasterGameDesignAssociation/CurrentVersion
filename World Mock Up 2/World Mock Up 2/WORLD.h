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

_WORLD contains all of the basic data structures that will be used to control
the basic function of the world that the game will be using

the wrapper class world contains 3 sub classes tile, object, actor, which are used
to manage there respective entity type

*/

#ifndef _WORLD
#define _WORLD

#include "COLLECTIONS.h"

/*
contains
	vector<tile> tileSet - This is the set of tiles used in the world
	vector<object> objectSet - This is the set of objects used in the world
	vector<actor> actorSet - This is the set of actors used in the world
	int* tileLocations - This is the locations of all of the current tiles
	int* objectLocations - This is the locations of all of the current objects
	int* actorLocations - This is the locations of all of the current actors
	unsigned int dimensions[2] - This is the current dimensions of the world
	unsigned int playerStartingPosition[2] - This is the starting position for
	the player, making a predefined entrance will prevent the player from 
	initially being placed in a wall

world is used to control and maintain all of the in world
game elements
*/
class world //: actor, player, object, tile
{
	private:
		//Belongs to FileReader
		FileReader* gameFile;

		vector<tile> tileSet;
		vector<object> objectSet;

		int* tileLocations;
		int* objectLocations;
		int* actorLocations;
		int resolution;
		unsigned int dimensions[2];
		unsigned int playerStartLocation[2];
		counter* timingFunction;
		int frameCounter;
		int frameStop; 

	public:

		//The actor vector has been put into public temporarily for
		//The HDMI event this needs to be made private again once the movement
		//update functions have been made correctly
		vector<actor> actorSet;
		world(string worldFile);
		void setTiles(vector<tile> newTileSet);
		void setObjects(vector<object> newObjectSet);
		void setActor(vector<actor> newActorSet);
		void changeDimension(unsigned int size[2]);
		void addTile(tile block);
		void addObject(object block);
		void addActor(actor character);

		void removeTile(unsigned int ID);
		void removeObject(unsigned int ID);
		void removeActor(unsigned int ID);
		void setTileLocation(unsigned int pos[2], unsigned int ID);
		void setObjectLocation(unsigned int pos[2], unsigned int ID);
		//void setActorLocation(unsigned int pos[2], unsigned int ID);
		void swapTile(tile newTile, unsigned int ID);
		void swapObject(object newObject, unsigned int ID);
		void swapActor(actor newCharacter, unsigned int ID);
		void changeResolution(int newResolution);
		void updateActorPositions(void);
		void populateWorld(void);

		void printLog(void);
		
		tile getTile(unsigned int ID);
		object getObject(unsigned int ID);
		actor getCharacter(unsigned int ID);
		vector<tile> getTileSet(void);
		vector<object> getObjectSet(void);
		vector<actor> getActorSet(void);

		bool getTileCollision(unsigned int ID);
		bool getObjectCollision(unsigned int ID);
		unsigned int* getPlayerStart(void);

		void changeTilePassthrough(unsigned int ID, bool passable);
		void changeObjectPassthrough(unsigned int ID, bool passable);
		void changePlayerStart(unsigned int playerLocation[2]);
		
		int checkTileMap(unsigned int pos[2]);
		int checkObjectMap(unsigned int pos[2]);
		
		int getX(void);
		int getY(void);
		int getResolution(void);

		int getTileSetSize(void);
		int getObjectSetSize(void);

		//Created by Ryan for the NPC 
		void updateNPCSet(player* currentPlayer, renderer* act);
		//Added by ryan davis
		//Temporary variables until timer is finished
		int detectionRange;
		int getFrameStop(void);
		int getFrameCounter(void);

		void updateWorldClock(void);
};

#endif // !_WORLD
//3043 as of 09/03/2014