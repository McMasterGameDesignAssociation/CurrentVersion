#ifndef _ITEM_METHODS
#define _ITEM_METHODS

#include "ITEM.h"

item::item(void)
{
	this -> value = 0;
	this -> whieght  = 0;
	this -> ID = 0;
	this -> itemClass = food;
}

item::item(unsigned int initValue, unsigned int initCost, itemType newType)
{
	this -> ID = 0;
	this -> value = initValue;
	this -> whieght  = initCost;
	this -> itemClass = newType;
}

#endif