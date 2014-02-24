#ifndef _WORLD_OBJECT_METHODS
#define _WROLD_OBJECT_METHODS

#include "OBJECT.h"

///OBJECT METHODS
object::object(void)
{
	ID = 0;
	face = Up;
	passThrough = false;
	description = "This is an empty object";
}

void object::setObject(direction newFace, bool passable, string newBitMapName, string newDescription)
{
	face = newFace;
	passThrough = passable;
	description = newDescription;
}

void object::printLog(void)
{
	cout << "Current object: " << description << endl;
	cout << "ID: "<< ID << endl;
	cout << "Pass through: " << passThrough << endl;
	cout << "Face: " << face << endl << endl;
}

//Please do not use this function it is designed to be private
void object::changeID(unsigned int newID) {ID = newID;}
void object::changePassThrough(bool passable){passThrough = passable;}
void object::changeFace(direction newFace){face = newFace;}

int object::getID(void) {return ID;}
direction object::getFace(void) {return face;}
bool object::getPassThrough(void) {return passThrough;}
#endif