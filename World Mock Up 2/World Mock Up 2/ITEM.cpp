#ifndef _ITEM_METHODS
#define _ITEM_METHODS

#include "ITEM.h"

item::item(void)
{
	this -> value = 0;
	this -> cost  = 0;
	this -> ID = 0;
	this -> itemClass = food;
}

item::item(unsigned int newID, unsigned int initValue, unsigned int initCost, itemType newType)
{
	this -> ID = newID;
	this -> value = initValue;
	this -> cost  = initCost;
	this -> itemClass = newType;
}

#endif