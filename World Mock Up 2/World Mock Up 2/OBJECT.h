/*
COPYRIGHT BENJAMIN ISHERWOOD 25/02/2014
THIS SOFTWARE IS INTENDED FOR OPEN SOURCE USE, REDISTRIBUTION
IS ENCOURAGED

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _WORLD_OBJECTS
#define _WORLD_OBJECTS

#include "COLLECTIONS.h"

/*

The object class is used to store the information that is
contained in each object in the world, where objects
are passive but the player can interact with them
i.e. doors, security systems, shelves, etc.
enum
	direction{up, left, down, right] - This is used as a local type
									   to track the direction of an
									   object

variables
	unsigned int ID - ID is used to distinguish each object from each other
	object::direction face - Face determines the direction
							 the front of the object is facing
	bool passThrough - This determines if the player will collide with
					   the current object
	string bitMapName - This determines the directory where every
							  texture for each version of the object's
							  sprite is located
	string description - This will be used to describe the object in the
						 logs
*/
class object : public entity, public gamepiece
{
	private:
		unsigned int size[2];

	public:
		object(void);
		void setObject(direction newFace, bool passable, string newBitMapName, string newDescription);
		//Logging function
		void printLog(void);

};
#endif