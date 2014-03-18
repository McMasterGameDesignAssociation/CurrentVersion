#ifndef UTILITIES
#define UTILITIES

#include "COLLECTIONS.h"

namespace utilities
{
	static queue<int> numberSeries;
	static int randomNumberGenerator(double newSeed)
	{
		int* seed;
		int temp;
		seed = (int*)malloc(sizeof(int));
		#if (defined(_WIN32) || defined(_WIN64))
			temp = GetTickCount();
			temp += (int)((int)time(NULL) - (int)&seed*cos((double)newSeed/((2*PI)*sin(temp)+1)));
			srand(temp);
			return rand();//abs((int)(rand()*cos((double)GetTickCount()/1000)));
		#else
			temp = (int)time(NULL);
			temp += (int)((int)&seed*cos(newSeed));
			srand(temp);
			return rand();
		#endif

	}

	static void makeRandomNumber(int newSeed) {numberSeries.push(randomNumberGenerator(newSeed));}

	static int getRandomNumber(void)
	{
		if(!numberSeries.empty())
		{
			int check = numberSeries.front();
			numberSeries.pop();
			return check;
		}
		else return randomNumberGenerator((int)time(NULL));
	}
}

#endif