#ifndef _TIMER_METHODS
#define _TIMER_METHODS

#include "TIMER.h"

counter::counter(void)
{
	timing = int(time(0));
	count = 0;
	increment = 0;
}

void counter::updateTiming(void) {checkTiming() ? timing = int(time(0)) : timing;}
void counter::updateCount(countChoice update) {update == inc ? count++ : count = 0;}
bool counter::checkTiming(void) {return (timing != time(0)) ? true : false;}
void counter::updateInc(int newInc) {increment = newInc;}
void counter::updateSystem(void) {checkTiming() ? (updateTiming(), updateInc(count), updateCount(reset)) : updateCount(inc);}
int counter::getInc(void) {return increment;}
int counter::getTiming(void) {return timing;}

#endif