#ifndef _TILE_METHODS
#define _TILE_METHODS

#include "TILE.h"

///TILE METHODS
tile::tile(void)
{
	ID = 0;
	passThrough = false;
	description = "This is an empty tile";
}

/*
inputs
	unsigned int newID - The ID that will replace the
				current ID
	bool passable - This the boolean that 
					determines passThrough
	string bitMap - This sets the new bit map
					directory

setTile is used to completely change an existing tile
*/
void tile::setTile(bool passable, string bitMap, string newDescription)
{
	passThrough = passable;
	description = newDescription;
}

/*
input
	void
output
	void

printLog is used to print the current
values stored in the tile to the prompt

*/
void tile::printLog(void)
{
	cout << "Current tile: " << description << endl;
	cout << "ID: "<< ID << endl;
	cout << "Pass through: " << passThrough << endl;
}
#endif