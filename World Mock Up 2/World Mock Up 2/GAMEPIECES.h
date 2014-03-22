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
#ifndef GAMEPIECES
#define GAMEPIECES

#include "SYSTEMCOLLECTIONS.h"
/*
gamepiece is a class that is used for all of the bits needed for
game pieces, i.e. everything that the player can interact with
this applies to the actors, player, and objects
*/
class gamepiece
{
private:
	/*This tracks the direction the actor is facing
	entities up, left, down, right*/
	direction face;

protected:
	unsigned int* position;
	const char* bitMapName;
	void updatePosition(void);
	unsigned int size;

public:
	direction getFace(void) const;
	unsigned int* getPosition(void) const;
	const char* getBitMapName(void) const;

	int vertices[12];
	double shadeVertices[18];
	void changePosition(unsigned int pos[2]);
	void changeBitMap(const char* newBitMap);
	void setDirection(direction newFace);
	void incrementDirection(void);
	void decrementDirection(void);
};

#endif