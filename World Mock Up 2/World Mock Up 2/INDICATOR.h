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
#ifndef INDICATORS
#define INDICATORS

#include "SYSTEMCOLLECTIONS.h"

class indicator
{
protected:
	int* position;
	int* size;
	unsigned int ID;
	const char* bitmapName;

public:
	int* getPosition(void) const;
	int* getSize(void) const;
	unsigned int getID(void) const;
	const char* getBitMapName(void) const;

	void setSize(int* newSize);
	void setPosition(int* newPosition);
	void changeID(unsigned int newID);
	void setBitmapName(const char* newName);
};

#endif