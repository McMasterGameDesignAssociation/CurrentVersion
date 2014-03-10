/*
COPYRIGHT BENJAMIN ISHERWOOD 25/02/2014
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
#ifndef _TIMER_H
#define _TIMER_H

#include <ctime>
//#include "COLLECTIONS.h"
enum countChoice{inc, reset};
class counter
{

private:
	int timing;
	int count;
	/*This is the number of cycles in a ms*/
	int increment;
	/*this will either inc, or reset the counter*/
	void updateCount(countChoice update);
	bool checkTiming(void);
	void updateInc(int newInc);
	void updateTiming(void);

public:

	counter(void);
	/*This will check the timing value*/
	void updateSystem(void);
	int getInc(void);
	int getTiming(void);
};

#endif