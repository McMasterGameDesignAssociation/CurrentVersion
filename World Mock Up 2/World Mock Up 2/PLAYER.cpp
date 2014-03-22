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
#ifndef _PLAYER_METHODS
#define _PLAYER_METHODS

#include "PLAYER.h"

player::player(void)
{
	//Added by Ryan Davis
	//Player variable initializations
	position = new unsigned int[2];
	suspicious = false;

}

player::player(world* map)
{
	//Added by Ryan Davis
	//Player variable initializations
	suspicious = false;
	position = new unsigned int[2];
	unsigned int* temp;
	temp = map -> getPlayerStart();
	position[0] = temp[0]*map -> getResolution(), 
	position[1] = temp[1]*map -> getResolution();
	size = map -> getResolution();
	for(int i = 0; i < 12; i++) vertices[i] = 0;
	for(int i = 0; i < 18; i++) shadeVertices[i] = 1;
	bitMapName = "None";
	description = "This is an empty player";
	speed = 0;
	animationStep = 0;
	setDirection(Up);
	updatePosition();
	temp = NULL;
	delete temp;
}

void player::changeSize(int newSize) {size = newSize;}

/*
inputs
	current world, new x and new y positions
output
	void
This function checks the current player's position against the tiles and the object
layers to check if motion is possible. This is done by taking the X and Y value of the
player and then dividing by the square 64 then checking it against the tile map at 
that location tileLocation(x,y) = posX/64, posY/64
*/
//Optimized to use pointers by Ryan Davis
void player::checkMovement(world *map, int x, int y)
{
	unsigned int posOne[2];
	unsigned int posTwo[2];
	unsigned int posThree[2];
	unsigned int posFour[2];
	int speed  = getSpeed();

	x = (x >= 1)  ?  speed : x;
	x = (x <= -1) ? -speed : x;
	y = (y >= 1)  ?  speed : y;
	y = (y <= -1) ? -speed : y;
	
	speed = map -> getResolution() - speed;

	//This is a check of the lower bound of movement
	posOne[0] = (x + position[0])/map -> getResolution(), posOne[1] = (y + position[1])/map -> getResolution();
	//This is a check of the upper bound of movement
	posTwo[0] = (x + speed + position[0])/map -> getResolution(), posTwo[1] = (y + speed + position[1])/map -> getResolution();
	//This is a check of the lower bound of movement
	posThree[0] = (x + position[0])/map -> getResolution(), posThree[1] = (y + speed + position[1])/map -> getResolution();
	//This is a check of the upper bound of movement
	posFour[0] = (x + speed + position[0])/map -> getResolution(), posFour[1] = (y + position[1])/map -> getResolution();

	if(map -> getTileCollision(map -> checkTileMap(posOne)) 
		&& map -> getTileCollision(map -> checkTileMap(posTwo))
		&& map -> getTileCollision(map -> checkTileMap(posThree)) 
		&& map -> getTileCollision(map -> checkTileMap(posFour))) 
	{
		position[0] = x + position[0], position[1] = y + position[1];
		updatePosition();
	}
}

//void player::followMouse(int pos[2], int screenDim[2])
//{
//	pos[0] -= screenDim[0]/2, pos[1] -= screenDim[1]/2;
//	if((pos[0] > 0 && pos[1] > 0 && pos[0] > pos[1]) ||
//		(pos[0] > 0 && pos[1] < 0 && pos[0] > abs(pos[1])))
//		setDirection(Right);
//	else if((pos[0] > 0 && pos[1] < 0 && pos[0] < abs(pos[1])) || 
//		(pos[0] < 0 && pos[1] < 0 && abs(pos[0]) < abs(pos[1])))
//		setDirection(Up);
//	else if((pos[0] < 0 && pos[1] < 0 && abs(pos[0]) > abs(pos[1])) ||
//		(pos[0] < 0 && pos[1] > 0 && abs(pos[0]) > pos[1]))
//		setDirection(Left);
//	else if((pos[0] < 0 && pos[1] > 0 && abs(pos[0]) < pos[1]) ||
//		(pos[0] > 0 && pos[1] > 0 && pos[0] < pos[1]))
//		setDirection(Down);
//}

//Added by ryan davis for suspicion
bool player::getSuspicious(void){return suspicious;}
void player::setSuspicous(bool newSuspicion){suspicious = newSuspicion;}

#endif