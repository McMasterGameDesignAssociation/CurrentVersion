#ifndef _NPC_METHODS
#define _NPC_METHODS

#include "NPCHandler.h"

#ifndef _NPC_AI
#define _NPC_AI

pathfinding theWholePathfindingClass = pathfinding();
vector<node*> thePath;
bool readyToPathfind = true;
bool foundPlayer = false;
bool absolutelyDoOnce = true; // create map for all npcs
bool inMiddleOfPathfinding = false;
int aCharacterPosition[2];
int pCharacterPosition[2];

vector<node*> findPlayer(actor &aCharacter, world *map, player *pCharacter)
{

	aCharacterPosition[0] = aCharacter.getPosition()[0];
	aCharacterPosition[1] = aCharacter.getPosition()[1];

	pCharacterPosition[0] = pCharacter->getPosition()[0];
	pCharacterPosition[1] = pCharacter->getPosition()[1];

	vector<node*> thePath = theWholePathfindingClass.findPath(aCharacterPosition, pCharacterPosition);
	return thePath;
}

void goToPlayerAI(actor &aCharacter, world *map, player *pCharacter)
{

	if (absolutelyDoOnce)
	{
		theWholePathfindingClass.generateMap(map);
		absolutelyDoOnce = false;
	}

	if (readyToPathfind) {
		readyToPathfind = false;
		thePath = findPlayer(aCharacter, map, pCharacter); // create path to target
	}

	//// Pick one of the two below:
	//inMiddleOfPathfinding = (thePath.size() > 1) ? true : false; // If the actor more than one tile away, start a new a path to find
	inMiddleOfPathfinding = false; 	// always update path


	if (thePath.empty() == false)
	{
//		inMiddleOfPathfinding = true;
		node* nextNode = thePath.back();
		//thePath.pop();

		///	If we're not at the node yet
		if (floor(aCharacter.getPosition()[0]/64) != nextNode->location[0] ||
			floor(aCharacter.getPosition()[1]/64) != nextNode->location[1]) 
		{
			double probabilities[4] = { 0, 0, 0, 0 }; // up left down right
			
			if (aCharacter.getPosition()[0] > nextNode->location[0] * 64) // if actor is right of target , go left
				//aCharacter.setDirection(Left);
				probabilities[1] = 0.5;
			else if (aCharacter.getPosition()[0] < nextNode->location[0]*64)
				//aCharacter.setDirection(Right);
				probabilities[3] = 0.5;
			if (aCharacter.getPosition()[1] > nextNode->location[1]*64) // if actor is above target, go down
				//aCharacter.setDirection(Down);
				probabilities[2] = 0.5;
			else if (aCharacter.getPosition()[1] < nextNode->location[1]*64)
				//aCharacter.setDirection(Up);
				probabilities[0] = 0.5;

			aCharacter.changeDirection(probabilities);
			aCharacter.setMoving(true);
		}
		else  /// We're at the node, so pop it
		{ 
			thePath.erase(thePath.end()-1);
			aCharacter.setMoving(false);
		}
	}
	else // path empty
	{
		/// if we've reached the end of the path, wait
		if (!foundPlayer && !readyToPathfind && aCharacter.getPosition()[0] - pCharacterPosition[0] == 0 && aCharacter.getPosition()[1] - pCharacterPosition[1] == 0)
		{
			pCharacterPosition[0] = -1000;
			pCharacterPosition[1] = -1000;
			foundPlayer = true;
		}
		/// if target is more than 2 tiles away, pathfind
		if (!inMiddleOfPathfinding && abs((int)aCharacter.getPosition()[0] - (int)pCharacter->getPosition()[0]) + abs((int)aCharacter.getPosition()[1] - (int)pCharacter->getPosition()[1]) > 2*64) //5 * 64)
		{
			readyToPathfind = true;
			inMiddleOfPathfinding = true;
			foundPlayer = false;
		}
	}
}

void turnAI(actor &aCharacter, world *map, player *pCharacter){
	int * seedy;
	seedy = new int[0];
	srand((int)&seedy);
	delete[] seedy;
	int randomNumNPC = getRandomNumber()%10;
	if(randomNumNPC < 8 && randomNumNPC > 2)
	{
		aCharacter.setMoving(true);
		aCharacter.incrementDirection();
	}
	//else if(randomNumNPC < 2) aCharacter.AI = randomMovement;
	else aCharacter.setMoving(false);
}
void stopAI(actor &aCharacter, world *map, player *pCharacter)
{aCharacter.setMoving(false);}
void randomMovement(actor &aCharacter, world *map, player *pCharacter)
{
	// Logic
	// NPC tracking if surrounding squares are passable
	//up
	unsigned int upTile[2], rightTile[2], downTile[2], leftTile[2];
	double temp[4];
	upTile[0]= (aCharacter.getPosition()[0]/map -> getResolution());
	upTile[1] = (aCharacter.getPosition()[1]/map -> getResolution()) + 1;
	//right
	rightTile[0]= (aCharacter.getPosition()[0]/map -> getResolution()) + 1;
	rightTile[1] = (aCharacter.getPosition()[1]/map -> getResolution());
	//down
	downTile[0]= (aCharacter.getPosition()[0]/map -> getResolution());
	downTile[1] = (aCharacter.getPosition()[1]/map -> getResolution()) - 1;
	//left
	leftTile[0]= (aCharacter.getPosition()[0]/map -> getResolution()) - 1;
	leftTile[1] = (aCharacter.getPosition()[1]/map -> getResolution());
	if(map -> getTileCollision(map -> checkTileMap(upTile))) temp[0] = 1;
	else temp[0] = 0;
	if(map -> getTileCollision(map -> checkTileMap(leftTile))) temp[1] = 1;
	else temp[1] = 0;
	if(map -> getTileCollision(map -> checkTileMap(downTile))) temp[2] = 1;
	else temp[2] = 0;
	if(map -> getTileCollision(map -> checkTileMap(rightTile))) temp[3] = 1;
	else temp[3] = 0;
	
	int bias[4] = {0, 0, 0, 0};
	switch(aCharacter.getFace())
	{
	case Up:
		bias[0] = 2000;
		break;
	case Left:
		bias[1] = 2000;
		break;
	case Down:
		bias[2] = 2000;
		break;
	case Right:
		bias[3] = 2000;
		break;
	}
	double probabilities[] = {(getRandomNumber()%100 + bias[0])*temp[0], 
							  (getRandomNumber()%100 + bias[1])*temp[1],
							  (getRandomNumber()%100 + bias[2])*temp[2], 
							  (getRandomNumber()%100 + bias[3])*temp[3]}; 
	if(aCharacter.isFacingPlayer(pCharacter) && pCharacter -> getSuspicious()) aCharacter.increaseAlert();
	else if(aCharacter.getAlert() > 0) aCharacter.decreaseAlert();
 
	aCharacter.setMoving(true);
	srand((int)&probabilities*(int)time(NULL));
	int randomNum = (getRandomNumber())%1000;
	if(aCharacter.getAlert() == 0 && aCharacter.getIsHittingWall() || (randomNum > 953 || randomNum < 31)) aCharacter.changeDirection(probabilities);
    
	//Detect movement ends here
    aCharacter.setMoving(true);
		if(aCharacter.isFacingPlayer(pCharacter) && aCharacter.getAlert() > 0)
        { //if actor can see vector
			aCharacter.setMoving(true);
			if(abs( (double) pCharacter-> getPosition()[0] - aCharacter.getPosition()[0]) > 32 || abs( (double) pCharacter -> getPosition()[1] - aCharacter.getPosition()[1]) > 32)
			{ //if the actor is greater than 32 pixels away from the player (if it isn't, there is no need to move)
				if( (abs( (double) pCharacter -> getPosition()[0] - aCharacter.getPosition()[0]) > abs( (double) pCharacter -> getPosition()[1] - aCharacter.getPosition()[1])))
				{ //if the x is further away than the y then move x. otherwise move in y.
					if (aCharacter.getPosition()[0] < pCharacter -> getPosition()[0] + 32 )
						aCharacter.setDirection(Right);
					else if (aCharacter.getPosition()[0] > pCharacter -> getPosition()[0] - 32)
						aCharacter.setDirection(Left);
				}
				else
				{
					if (aCharacter.getPosition()[1] < pCharacter -> getPosition()[1] + 32)
						aCharacter.setDirection(Up);
					else if (aCharacter.getPosition()[1] > pCharacter -> getPosition()[1] - 32)
						aCharacter.setDirection(Down);
				}
			}
			else aCharacter.setMoving(false);
		}
}
#endif

///ACTOR METHODS
actor::actor(void)
{
	position = new unsigned int[2];
	position[0] = 0, position[1] = 0;
	ID = 0;
	setDirection(Up);
	animationStep = 0;
	bitMapName = "None";
	description = "This is an empty character";
	updatePosition();
	AI = stopAI;
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

void actor::runAI(world *map, player *currentPlayer) 
{AI(*this, map, currentPlayer);}

//void actor::changeDirection(direction newFace) {face = newFace;}
//string actor::getDescription(void) {return description;}
//int actor::getID(void) {return ID;}
//actor::direction actor::getFace(void) {return face;}

//Beginning of ryan
actor::actor(unsigned int posX, unsigned int posY, int newSpeed, const char* newBitmap,  actorCallback newAI, world *map)
{
	position = new unsigned int[2];
	position[0] = posX, position[1] = posY;
    speed = newSpeed;
    setDirection(Up);
	size = map -> getResolution();
	bitMapName = newBitmap;
    description = "This is an empty character";
    visionRange = 5*64;
    alert = 0;
    maxVision = visionRange + 4*64;
	for(int i = 0; i < 18; i++) shadeVertices[i] = 1;
	animationStep = 0;
	updatePosition();
	AI = newAI;
}

void actor::increaseAlert(void)
{
	alert = 1;
	visionRange = maxVision;
	speed = 8;
}
void actor::decreaseAlert(void)
{
	alert=0;
	visionRange=5*64;
	speed = 4;
}

int actor::getAlert(void) {return alert;}
void actor::setSeesPlayer(bool canSeePlayer) {this->playerWithinRange = canSeePlayer;}
bool actor::getSeesPlayer(void) {return playerWithinRange;}
void actor::setVisionRange(void){}
double actor::getVisionRange(void) {return visionRange;}

/* checkMovement
* this function checks to make sure there is no block preventing movement
* same as the function for the player 
* made by ben
*/
void actor::checkMovement(world *map, int x, int y)
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
        
        speed = 64 - speed;

        //This is a check of the lower bound of movement
		posOne[0] = (x + getPosition()[0] + 16)/map->getResolution(), posOne[1] = (y + getPosition()[1] + 14)/map->getResolution();
        //This is a check of the upper bound of movement
        posTwo[0] = (x + speed + getPosition()[0] - 16)/map->getResolution(), posTwo[1] = (y + speed + getPosition()[1] - 32)/map->getResolution();

        //This is a check of the lower bound of movement
        posThree[0] = (x + getPosition()[0] + 16)/map->getResolution(), posThree[1] = (y + speed + getPosition()[1] - 32)/map->getResolution();
        //This is a check of the upper bound of movement
        posFour[0] = (x + speed + getPosition()[0] - 16)/map->getResolution(), posFour[1] = (y + getPosition()[1] + 14)/map->getResolution();

	    if(map -> getTileCollision(map ->checkTileMap(posOne)) 
		&& map -> getTileCollision(map -> checkTileMap(posTwo))
		&& map -> getTileCollision(map -> checkTileMap(posThree)) 
		&& map -> getTileCollision(map -> checkTileMap(posFour)))        
		{
			//position[0] = x + position[0], position[1] = y + position[1];
            posOne[0] = x + getPosition()[0], posOne[1] = y + getPosition()[1];
            changePosition(posOne);
			isHittingWall = false;
        }
		else isHittingWall = true;
		updatePosition();
}

//Optimized to pointers for speed boost
//By Ryan Davis
void actor::updateMovement(world *map, renderer *act)
{
    if (getMoving() == true)
    {
		if (getFace() == Up) 
			checkMovement(map, 0, 1);
		else if (getFace() == Right)
			checkMovement(map, 1, 0);
		else if (getFace() == Left)  
			checkMovement(map, -1, 0);                      
        else if (getFace() == Down)
            checkMovement(map, 0, -1);
    }
	if(getMoving()) act -> animateActor(*this, true);
}

bool actor::getIsHittingWall(void) {return isHittingWall;}
void actor::setIsHittingWall(bool hitWall){isHittingWall = hitWall;}

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
	if( (abs( (double) position[0] - currentPlayer -> getPosition()[0] ) < visionRange) 
		&& (abs((double) position[1] - currentPlayer -> getPosition()[1]) < visionRange))
	{
		if(getFace() == Up && currentPlayer -> getPosition()[1] > position[1]
			|| getFace() == Right && currentPlayer -> getPosition()[0] > position[0]
			|| getFace() == Down && currentPlayer -> getPosition()[1] <  position[1]
			|| getFace() == Left && currentPlayer -> getPosition()[0] < position[0])
			return true;
    } 
	return false;
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

	srand((int)&tempHeading+((int)&probabilities%100+1));
	int randomNum = (getRandomNumber()%100);
	//if(randomNum < 30) AI = turnAI;

	probabilities[0] = probabilities[0]/total;
	probabilities[1] = probabilities[1]/total;
	probabilities[2] = probabilities[2]/total;
	probabilities[3] = probabilities[3]/total;

	for(int i = 4; i--;)
	{
		for(int j = 4; j--;)
		{
			if(probabilities[i] <= probabilities[j]) 
			{
				total = probabilities[i], 
				probabilities[i] = probabilities[j], 
				probabilities[j] = total,
				tempHeading = directions[i],
				directions[i] = directions[j],
				directions[j] = tempHeading;
			}
		}
	}
	if(randomNum < probabilities[0]*100) setDirection(directions[0]);
	else if(randomNum >= probabilities[0]*100 
		&& randomNum < (probabilities[1] + probabilities[0])*100) 
		setDirection(directions[1]);
	else if(randomNum >= (probabilities[1] + probabilities[0])*100 
		&& randomNum < (probabilities[0] + probabilities[1] + probabilities[2])*100)
		setDirection(directions[2]);
	else  setDirection(directions[3]);
}
void actor::setMoving(bool moving) {isMoving = moving;}
bool actor::getMoving(void) {return isMoving;}
////////////end of new ryan
#endif