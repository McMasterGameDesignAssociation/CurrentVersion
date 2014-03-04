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
}

player::player(world map)
{
	unsigned int* temp;
	temp = map.getPlayerStart();
	this -> position[0] = temp[0]*map.getResolution(), 
	this -> position[1] = temp[1]*map.getResolution();
	this -> size = 64;
	for(int i = 0; i < 12; i++) this-> vertices[i] = 0;
	for(int i = 0; i < 18; i++) this-> shadeVertices[i] = 1;
	this -> bitMapName = "None";
	this -> description = "This is an empty player";
	this -> speed = 0;
	this -> animationStep = 0;
	this -> face = Up;
	updatePosition();
}

unsigned int player::getPositionX(void) {return position[0];}
unsigned int player::getPositionY(void) {return position[1];}
int player::getSpeed(void) {return speed;}

string player::getBitMap(void) {return bitMapName;}
string player::getDescription(void) {return description;}
void player::setSpeed(int movement) {this->speed = movement;}
void player::changeSize(int newSize) {this->size = newSize;}
void player::changeDescription(string newDescription) {description = newDescription;}

void player::updatePosition(void) 
{
	this->vertices[0]  = position[0] - (size/2), this->vertices[1]  = position[1] - (size/2),
	this->vertices[2]  = position[0] + (size/2), this->vertices[3]  = position[1] - (size/2),
	this->vertices[4]  = position[0] - (size/2), this->vertices[5]  = position[1] + (size/2),
	this->vertices[6]  = position[0] - (size/2), this->vertices[7]  = position[1] + (size/2),
	this->vertices[8]  = position[0] + (size/2), this->vertices[9]  = position[1] + (size/2),
	this->vertices[10] = position[0] + (size/2), this->vertices[11] = position[1] - (size/2);

	for(int i = 0; i < 18; i++) this-> shadeVertices[i] = 1;
}
void player::changeBitMap(string newBitMap) {bitMapName = newBitMap;}

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
void player::checkMovement(world map, int x, int y)
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
	
	speed = map.getResolution() - speed;

	//This is a check of the lower bound of movement
	posOne[0] = (x + position[0])/map.getResolution(), posOne[1] = (y + position[1])/map.getResolution();
	//This is a check of the upper bound of movement
	posTwo[0] = (x + speed + position[0])/map.getResolution(), posTwo[1] = (y + speed + position[1])/map.getResolution();
	//This is a check of the lower bound of movement
	posThree[0] = (x + position[0])/map.getResolution(), posThree[1] = (y + speed + position[1])/map.getResolution();
	//This is a check of the upper bound of movement
	posFour[0] = (x + speed + position[0])/map.getResolution(), posFour[1] = (y + position[1])/map.getResolution();

	if(map.getTileCollision(map.checkTileMap(posOne)) 
		&& map.getTileCollision(map.checkTileMap(posTwo))
		&& map.getTileCollision(map.checkTileMap(posThree)) 
		&& map.getTileCollision(map.checkTileMap(posFour))) 
	{
		position[0] = x + position[0], position[1] = y + position[1];
		updatePosition();
	}
}

void player::changeDirection(int pos[2], int screenDim[2])
{
	pos[0] -= screenDim[0]/2, pos[1] -= screenDim[1]/2;
	if((pos[0] > 0 && pos[1] > 0 && pos[0] > pos[1]) ||
		(pos[0] > 0 && pos[1] < 0 && pos[0] > abs(pos[1])))
		face = Right;
	else if((pos[0] > 0 && pos[1] < 0 && pos[0] < abs(pos[1])) || 
		(pos[0] < 0 && pos[1] < 0 && abs(pos[0]) < abs(pos[1])))
		face = Up;
	else if((pos[0] < 0 && pos[1] < 0 && abs(pos[0]) > abs(pos[1])) ||
		(pos[0] < 0 && pos[1] > 0 && abs(pos[0]) > pos[1]))
		face = Left;
	else if((pos[0] < 0 && pos[1] > 0 && abs(pos[0]) < pos[1]) ||
		(pos[0] > 0 && pos[1] > 0 && pos[0] < pos[1]))
		face = Down;
}

#endif