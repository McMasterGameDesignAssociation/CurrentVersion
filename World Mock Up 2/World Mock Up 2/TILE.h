#ifndef _TILE
#define _TILE

#include "COLLECTIONS.h"

/*
tile is used as the base unit of the world

variables
	unsigned int ID - An ID to track the tile through
			 the system

	bool passThrough - This boolean is used to
			 determine if the tile can be walked
			 over i.e. a pathway, or ones that 
			 can not be walked over i.e. a wall

	string bitMapName - This is the string that
			 will be used to determine the name
			 and the directory of the current
			 texture for the tile.
	string description - This will be used a documenting
						 tool, and will be used in the change logs
*/
class tile
{
private:

	unsigned int ID;
	bool passThrough;
	string description;

public:

	//Modifiers
	tile(void);
	void setTile(bool passable, string bitMap, string newDescription);
	void changeID(unsigned int newID);
	void changePassThrough(bool passable);
	void changeDescription(string newDescription);

	//Accessors
	int getID(void);
	bool getPassThrough(void);
	string getBitMapName(void);
	string getDescription(void);

	//Logging functions
	void printLog(void);

};

#endif