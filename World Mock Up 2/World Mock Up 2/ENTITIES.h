/*
COPYRIGHT BENJAMIN ISHERWOOD 21/03/2014
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
#ifndef ENTITIES
#define ENTITIES

//#include "COLLECTIONS.h"

/*
The entities is used as the top of the hierarchy for all of the game elements
that are stored in the world, this stores all of the general information
such as the ID and the descriptions of the entity
*/
#include "SYSTEMCOLLECTIONS.h"

class entity{

protected:
	bool passThrough;
	unsigned int ID;
	string description;

public:
	unsigned int getID(void) const;
	string getDescription(void) const;
	bool getPassThrough(void) const;

	void changePassThrough(bool passable);
	void changeID(unsigned int newID);
	void changeDescription(string newDescription);
};

#endif