#ifndef UTILITIES
#define UTILITIES

#include "COLLECTIONS.h"

namespace utilities
{
	static queue<int> numberSeries;
	static int randomNumberGenerator(double &newSeed)
	{
		int temp;
		#if (defined(_WIN32) || defined(_WIN64))
			temp = GetTickCount();
			if(numberSeries.size() > 0) newSeed += (int)&numberSeries.back();
			temp += (int)((int)time(NULL) - (int)&newSeed*cos((double)newSeed/((2*PI)*sin(temp)+1)));
			srand(temp);
			return rand();
		#else
			temp = (int)time(NULL);
			temp += (int)((int)&newSeed*cos(newSeed));
			srand(temp);
			return rand();
		#endif

	}

	static void makeRandomNumber(double newSeed) {numberSeries.push(randomNumberGenerator(newSeed));}

	static int getRandomNumber(void)
	{
		double newSeed = (double)time(NULL);
		if(!numberSeries.empty())
		{
			int check = numberSeries.front();
			numberSeries.pop();
			return check;
		}
		else return randomNumberGenerator(newSeed);
	}
}

#endif