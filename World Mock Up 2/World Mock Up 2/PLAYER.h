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