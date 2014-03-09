#ifndef _NPC_METHODS
#define _NPC_METHODS

#include "NPCHandler.h"

///ACTOR METHODS
actor::actor(void)
{
	ID = 0;
	face = Up;
	animationStep = 0;
	bitMapName = "None";
	description = "This is an empty character";
	updatePosition();
}
//
///*
//inputs
//	direction newFace - This defines the new direction of an actor
//	string newBitMapName - This defines the new bit map file name
//	string newDescription - This will set the new description of the
//							character
//output
//	void
//This function changes the current actor to the new one specified
//*/
//void actor::setActor(direction newFace, string newBitMapName, string newDescription)
//{
//	face = newFace;
//	bitMapName = newBitMapName;
//	description = newDescription;
//}
//
///*
//inputs
//	void
//output
//	void
//This function prints the change log for the current actor
//*/
void actor::printLog(void)
{
	cout << "Current actor: " << description << endl;
	cout << "ID: "<< ID << endl;
	cout << "Bit map name: " << bitMapName << endl << endl;
}
//
////This function should be private
void actor::changeID(unsigned int newID) {ID = newID;}
//void actor::changeDirection(direction newFace) {face = newFace;}
//string actor::getDescription(void) {return description;}
//int actor::getID(void) {return ID;}
//actor::direction actor::getFace(void) {return face;}
//string actor::getBitMapName(void) {return bitMapName;}
const char* actor::getBitMapName(void) {return bitMapName;}

//Beginning of ryan
actor::actor(unsigned int posX, unsigned int posY, int newSpeed, const char* newBitmap,  world *map)
{
	vPosition.x = posX, initialXPos = posX;
	vPosition.y = posY, initialYPos = posY;
    speed = newSpeed;
    face = Up;
	size = map -> getResolution();
	bitMapName = newBitmap;
    description = "This is an empty character";
    frameCounter = 0;
    visionRange = 5*64;
    alert = 0;
    maxVision = visionRange + 4*64;
	animationStep = 0;
	updatePosition();
}

int actor::getFrameCount() {return frameCounter;}
void actor::setFrameCount(int newFrameCount) {frameCounter = newFrameCount;}
bool actor::getMoving() {return isMovingToSpot;}
void actor::setMoving(bool isMoving) {this->isMovingToSpot = isMoving;}
int actor::getSpeed() {return speed;}
void actor::setSpeed(int newSpeed) {this->speed = newSpeed;}
ActorVector actor::getPosition() {return vPosition;}

void actor::setPosition(unsigned int x, unsigned int y)
{
        this->vPosition.x = x;
        this->vPosition.y = y;
}

void actor::moveto(unsigned int x, unsigned int y)
{        
}

/*
This version of the changeDirection function changes the
direction that the actor is facing by directly adding
in the new face direction
*/
void actor::changeDirection(direction newFace) {this->face = newFace;}
direction actor::getFace(void) {return face;}

void actor::increaseAlert(void)
{
        this->alert = 1;
        this->visionRange = maxVision;
        this->speed = 8;
}
void actor::decreaseAlert(void)
{
        this->alert=0;
        this->visionRange=5*64;
        this->speed = 4;
}

int actor::getAlert(void) {return alert;}
void actor::setSeesPlayer(bool canSeePlayer) {this->playerWithinRange = canSeePlayer;}
bool actor::getSeesPlayer(void) {return playerWithinRange;}
void actor::setVisionRange(void){}
double actor::getVisionRange(void) {return visionRange;}
int actor::getInitialXPos(void) {return initialXPos;}
int actor::getInitialYPos(void) {return initialYPos;}
int actor::getID(void) {return ID;}

/* checkMovement
* this function checks to make sure there is no block preventing movement
* same as the function for the player 
* made by ben
*/

//Optimized to pointers for speed boost by Ryan Davis

void actor::checkMovement(world *map, int x, int y)
{
        unsigned int posOne[2];
        unsigned int posTwo[2];
        unsigned int posThree[2];
        unsigned int posFour[2];
        int speed  = getSpeed();
        x = (x >= 1) ? speed : x;
        x = (x <= -1) ? -speed : x;
        y = (y >= 1) ? speed : y;
        y = (y <= -1) ? -speed : y;
        
        speed = 64 - speed;

        //This is a check of the lower bound of movement
        posOne[0] = (x + getPosition().x)/64, posOne[1] = (y + getPosition().y)/64;
        //This is a check of the upper bound of movement
        posTwo[0] = (x + speed + getPosition().x)/64, posTwo[1] = (y + speed + getPosition().y)/64;

        //This is a check of the lower bound of movement
        posThree[0] = (x + getPosition().x)/64, posThree[1] = (y + speed + getPosition().y)/64;
        //This is a check of the upper bound of movement
        posFour[0] = (x + speed + getPosition().x)/64, posFour[1] = (y + getPosition().y)/64;

	    if(map -> getTileCollision(map ->checkTileMap(posOne)) 
		&& map -> getTileCollision(map -> checkTileMap(posTwo))
		&& map -> getTileCollision(map -> checkTileMap(posThree)) 
		&& map -> getTileCollision(map -> checkTileMap(posFour)))        
		{
                posOne[0] = x + getPosition().x, posOne[1] = y + getPosition().y;
                setPosition(posOne[0], posOne[1]);
				this->isHittingWall = false;
        }
		else this->isHittingWall = true;
		updatePosition();
}

void actor::updatePosition(void)
{
	this -> vertices[0]  = vPosition.x - (size/2), this -> vertices[1]  = vPosition.y - (size/2),
	this -> vertices[2]  = vPosition.x + (size/2), this -> vertices[3]  = vPosition.y - (size/2),
	this -> vertices[4]  = vPosition.x - (size/2), this -> vertices[5]  = vPosition.y + (size/2),
	this -> vertices[6]  = vPosition.x - (size/2), this -> vertices[7]  = vPosition.y + (size/2),
	this -> vertices[8]  = vPosition.x + (size/2), this -> vertices[9]  = vPosition.y + (size/2),
	this -> vertices[10] = vPosition.x + (size/2), this -> vertices[11] = vPosition.y - (size/2);

	for(int i = 0; i < 18; i++) this-> shadeVertices[i] = 1;
}
//Optimized to pointers for speed boost
//By Ryan Davis
void actor::updateMovement(world *map, renderer *act)
{
    if (this->getMoving() == true)
    {
        if(frameCounter > 10 - speed)
		{
             if (face == Up) 
                 checkMovement(map, 0, 1);
             else if (face == Right)
                  checkMovement(map, 1, 0);
             else if (face == Left)  
				  checkMovement(map, -1, 0);                      
             else if (face == Down)
                  checkMovement(map, 0, -1);

             frameCounter = 0;
         }
         frameCounter ++;
    }
	act -> animateActor(*this, true);
}

bool actor::getIsHittingWall(void) {return isHittingWall;}
void actor::setIsHittingWall(bool hitWall){this->isHittingWall = hitWall;}
void actor::moveToPlayer()
{
        
}

/*
isFacingPlayer checks if the actor is able to see the player by
checking if they are with in the range of sight and then checking
if they are facing towards the player, returns true if the player
is visible to the NPC otherwise returns false

current bugs:
-The actor can see through walls

required update:
-raycasting that checks if there are objects between the player and the
actor, if there is an object in the way the actor should not be triggered
*/
bool actor::isFacingPlayer(player* currentPlayer)
{
	//This statement will be simplified the check does more than it should be doing
	if( (abs( (double) vPosition.x - currentPlayer -> getPositionX() ) < visionRange) 
		&& (abs((double) vPosition.y - currentPlayer -> getPositionY()) < visionRange))
	{
		if(face == Up && currentPlayer -> getPositionY() > vPosition.y
			|| face == Right && currentPlayer -> getPositionX() > vPosition.x
			|| face == Down && currentPlayer -> getPositionY() <  vPosition.y
			|| face == Left && currentPlayer -> getPositionX() < vPosition.x)
			return true;
		else return false;
    } 
}

/*
This version of change Direction takes in a list of
probabilities where the users define the probabilities
as: direction[Up, Left, Down, Right]

These probabilities are then placed into a random number
generator and the NPC moves thier look direction based 
on the result
*/
void actor::changeDirection(double probabilities[4])
{
	double total = probabilities[0] + probabilities[1] + 
		probabilities[2] + probabilities[3];

	direction directions[] = {Up, Left, Down, Right};
	direction tempHeading;

	srand((int)&directions*int(time(NULL))/((int)&probabilities%100+0.00001));
	int randomNum = (rand()%100);

	probabilities[0] = probabilities[0]/total;
	probabilities[1] = probabilities[1]/total;
	probabilities[2] = probabilities[2]/total;
	probabilities[3] = probabilities[3]/total;

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			if(probabilities[i] <= probabilities[j]) 
				total = probabilities[i], 
				probabilities[i] = probabilities[j], 
				probabilities[j] = total,
				tempHeading = directions[i],
				directions[i] = directions[j],
				directions[j] = tempHeading;
		
	if(randomNum < probabilities[0]*100)  face = directions[0];
	else if(randomNum >= probabilities[0] 
		&& randomNum < (probabilities[1] + probabilities[0])*100) 
		face = directions[1];
	else if(randomNum >= (probabilities[1] + probabilities[0])*100 
		&& randomNum < (probabilities[0] + probabilities[1] + probabilities[2])*100)
		face = directions[2];
	else  face = directions[3];
}

void actor::incrementDirection(void) {face++;}
////////////end of new ryan
#endif