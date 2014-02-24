#ifndef _ITEMS
#define _ITEMS

#include "COLLECTIONS.h"

class item
{

private:
	unsigned int ID;
	unsigned int value;
	unsigned int cost;
	itemType itemClass;

public:
	item(void);
	item(unsigned int newID, unsigned int initValue, unsigned int initCost, itemType newType);
};

#endif