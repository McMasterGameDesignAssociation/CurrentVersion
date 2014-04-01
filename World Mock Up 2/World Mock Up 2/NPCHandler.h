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
void goToPlayerAI(actor &aCharacter, world *map, player *pCharacter);

#endif
/*
The actor class is used to make instances of NPCs to be used in the world
*/
class actor : public entity, public gamepiece, public sprite
{
	private:
		double visionRange; //after being spotted the NPC vision increases
		unsigned int alert;
		double maxVision;
		bool playerWithinRange;
		bool isHittingWall;
		bool isMoving;
		unsigned int detectionRange;
	public:

				actorCallback AI;
                //Modifiers
				void checkMovement(world *map, int x, int y);
                actor(unsigned int posX, unsigned int posY, 
				int newSpeed, const char* newBitmap, 
				actorCallback newAI, world* map);
                actor(void);
                void setActor(direction newFace, string newBitMapName, string newDescription);
                void setMoving(bool isMoving);
                void setVisionRange(void);
                void increaseAlert(void);
                void decreaseAlert(void);
                void setSeesPlayer(bool);
                void setIsHittingWall(bool);

				void changeDirection(double probabilities[4]);
				bool isFacingPlayer(player* currentPlayer);

                //Accessor
				bool getMoving(void);
                double getVisionRange(void);
                int getAlert(void);
                bool getSeesPlayer(void);
                bool getIsHittingWall(void);

                //Update Function
                void updateMovement(world *map, renderer *act);
				void runAI(world *map, player *currentPlayer);

				//Logging function
                void printLog(void);
};

#endif