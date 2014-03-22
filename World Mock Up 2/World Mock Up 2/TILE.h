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
#ifndef _TILE
#define _TILE

#include "COLLECTIONS.h"

/*
tile is used as the base unit of the world

variables
	unsigned int ID - An ID to track the tile through
			 the system

	bool passThrough - This boolean is used to
			 determine if the tile can be walked
			 over i.e. a pathway, or ones that 
			 can not be walked over i.e. a wall

	string bitMapName - This is the string that
			 will be used to determine the name
			 and the directory of the current
			 texture for the tile.
	string description - This will be used a documenting
						 tool, and will be used in the change logs
*/

class tile: public entity
{
public:
	//Modifiers
	tile(void);
	void setTile(bool passable, string bitMap, string newDescription);
	//Logging functions
	void printLog(void);

};

#endif