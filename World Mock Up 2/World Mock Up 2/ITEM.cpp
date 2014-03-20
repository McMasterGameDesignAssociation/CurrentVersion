#ifndef _ITEM_METHODS
#define _ITEM_METHODS

#include "ITEM.h"

item::item(void)
{
	value = 0;
	whieght  = 0;
	ID = 0;
	itemClass = food;
}

item::item(unsigned int initValue, unsigned int initCost, itemType newType)
{
	 ID = 0;
	 value = initValue;
	 whieght  = initCost;
	 itemClass = newType;
}

#endif