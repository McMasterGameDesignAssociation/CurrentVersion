/*

_WORLD contains all of the basic data structures that will be used to control
the basic function of the world that the game will be using

the wrapper class world contains 3 sub classes tile, object, actor, which are used
to manage there respective entity type

*/

#ifndef _WORLD
#define _WORLD

#include "COLLECTIONS.h"

using namespace std;
class actor;
class tile;
class object;
class player;
class image;


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

		vector<tile> tileSet;
		vector<object> objectSet;
		vector<actor> actorSet;

		string characterPNG;
		string tilePNG;
		string objectPNG;
		string * actorPNG;

		int* tileLocations;
		int* objectLocations;
		int* actorLocations;
		int resolution;
		unsigned int dimensions[2];
		unsigned int playerStartLocation[2];

	public:

		world(unsigned int size[2]);
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
		void setActorLocation(unsigned int pos[2], unsigned int ID);
		void swapTile(tile newTile, unsigned int ID);
		void swapObject(object newObject, unsigned int ID);
		void swapActor(actor newCharacter, unsigned int ID);
		void changeResolution(int newResolution);
		void updateActorPositions(void);

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
};

#endif // !_WORLD