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
#ifndef _PLAYER
#define _PLAYER

#include "COLLECTIONS.h"
class world;

class player
{

private:
	unsigned int position[2];
	unsigned int size;
	string bitMapName;
	string description;
	void updatePosition(void);
	int speed;
	int playerResolution;

protected:


public:
	player(void);
	player(world map);
	int getSpeed(void);
	direction face;
	unsigned int getPositionX(void);
	unsigned int getPositionY(void);
	string getBitMap(void);
	string getDescription(void);
	void changeDescription(string newDescription);
	void changePosition(unsigned int pos[2]);
	void changeBitMap(string newBitMap);
	void checkMovement(world map, int x, int y);
	void setSpeed(int movement);
	void incAnimationStep(void);
	int getAnimationStep(void);
	//Base 7
	int animationStep;
	void changeDirection(int pos[2], int worldDim[2]);
	void changeSize(int newSize);

	int vertices[12];
	double shadeVertices[18];
};

#endif