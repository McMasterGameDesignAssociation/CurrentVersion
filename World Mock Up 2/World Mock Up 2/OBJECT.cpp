#ifndef _WORLD_OBJECT_METHODS
#define _WROLD_OBJECT_METHODS

#include "OBJECT.h"

///OBJECT METHODS
object::object(void)
{
	position = new unsigned int[2];
	ID = 0;
	setDirection(Up);
	passThrough = false;
	description = "This is an empty object";
}

void object::setObject(direction newFace, bool passable, string newBitMapName, string newDescription)
{
	setDirection(newFace);
	passThrough = passable;
	description = newDescription;
}

void object::printLog(void)
{
	cout << "Current object: " << description << endl;
	cout << "ID: "<< ID << endl;
	cout << "Pass through: " << passThrough << endl;
	cout << "Face: " << getFace() << endl << endl;
}
#endif