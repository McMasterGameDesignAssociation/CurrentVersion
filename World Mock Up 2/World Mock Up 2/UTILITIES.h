/*
COPYRIGHT BENJAMIN ISHERWOOD 14/03/2014
THIS SOFTWARE IS INTENDED FOR OPEN SOURCE USE, REDISTRIBUTION
IS ENCOURAGE

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
OTHER DEALINGS IN THE SOFTWARE.
*/
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