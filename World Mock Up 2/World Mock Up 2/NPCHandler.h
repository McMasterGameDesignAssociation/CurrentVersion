/*
COPYRIGHT RYAN DAVIS 25/02/2014
THIS SOFTWARE IS INTENDED FOR OPEN SOURCE USE, REDISTRIBUTION
IS ENCOURAGE

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
OTHER DEALINGS IN THE SOFTWARsE.
*/
#ifndef _NPCHANDLER
#define _NPCHANDLER

#include "COLLECTIONS.h"

/*
AI callback structure developed by Benjamin Isherwood
09/03/14 (March 9 2014)
*/
#ifndef AI_PROTO_TYPES
#define AI_PROTO_TYPES
void turnAI(actor &aCharacter, world *map, player *pCharacter);
void stopAI(actor &aCharacter, world *map, player *pCharacter);
void randomMovement(actor &aCharacter, world *map, player *pCharacter);
#endif
/*
contains
	enum direction - direction will be used to determine the direction 
					 that the actor is facing
	unsigned unsigned int ID - ID provides a unique ID for each actor so 
		    		  they can be tracked through the system
	direction face - face determines the standing direction the actor
					 is facing
	string bitMapName - bitMapName is the current name of the bitMap
						that the actor uses as a costume

The actor class is used to make instances of NPCs to be used in the world
*/
class actor
{
        private:
                
                unsigned int ID;
                const char* bitMapName;
                string description;
                ActorVector vPosition;
                unsigned int speed;
                bool isMovingToSpot;
                double visionRange; //after being spotted the NPC vision increases
                unsigned int alert;
                double maxVision;
                bool playerWithinRange;
                bool isHittingWall;
                int initialXPos;
                int initialYPos;
                int framCounterSpawn;
				bool movementHistory[4];
                unsigned int frameCounter; //the NPC will move after a set number of frames
				int size;

        public:

				actorCallback AI;
                //Modifiers
                actor(unsigned int posX, unsigned int posY, 
				int newSpeed, const char* newBitmap, 
				actorCallback newAI, world* map);
                actor(void);
				int animationStep;
				/*This tracks the direction the actor is facing
                entities up, left, down, right*/
                direction face;
				void incrementDirection(void);
                void setActor(direction newFace, string newBitMapName, string newDescription);
                void moveto(unsigned int x, unsigned int y);
                void changeID(unsigned int newID);
                void changeDirection(direction newFace);//
                void changeBitMapName(string newbitMapName);
                void setPosition(unsigned int x, unsigned int y);
                void setSpeed(int newSpeed);
                void setMoving(bool isMoving);
                void setVisionRange(void);
                void increaseAlert(void);
                void decreaseAlert(void);
                void setSeesPlayer(bool);
                void setIsHittingWall(bool);
                void setFrameCount(int);

				void changeDirection(double probabilities[4]);

				bool isFacingPlayer(player* currentPlayer);

                //Accessor
                int getID(void);
                direction getFace(void);
                const char* getBitMapName(void);
                string getDescription(void);
                int getSpeed();
                ActorVector getPosition();
                bool getMoving();
                void checkMovement(world *map, int x, int y);
                double getVisionRange(void);
                int getAlert(void);
                bool getSeesPlayer(void);
                bool getIsHittingWall(void);
                int getInitialXPos(void);
                int getInitialYPos(void);
                int getFrameCount(void);
				

				int vertices[12];
				double shadeVertices[18];
                //Logging function
                void printLog(void);
                //Update Function
                void updateMovement(world *map, renderer *act);
                //moveToPlayer, currently unused
                void moveToPlayer();
				void updatePosition(void);
				void runAI(world *map, player *currentPlayer);
};

#endif