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

item::item(unsigned int newID, unsigned int initValue, unsigned int initCost, itemType newType)
{
	 ID = newID;
	 value = initValue;
	 whieght  = initCost;
	 itemClass = newType;
}

unsigned int item::getID(void) const{return ID;}
unsigned int item::getValue(void) const{return value;}
unsigned int item::getWhieght(void) const{return whieght;}
int item::decreaseQuantity(void) {return quantity--;}
void item::increaseQuantity(void) {quantity++;}

#endif