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
#pragma once
#ifndef _TIMER
#define _TIMER

#include "COLLECTIONS.h"

class counter
{

private:
	int timing;
	int count;
	/*This is the number of cycles in a ms*/
	int increment;

public:

	counter(void);
	
	/*This will check the timing value*/
	bool checkTiming(void);
	int getInc(void);

	void updateTiming(void);
	/*this will either inc, or reset the counter*/
	void updateCount(countChoice update);
	void updateInc(int newInc);
	void updateSystem(void);

};



#endif