#pragma once

#ifndef _RENDERER
#define _RENDERER

#include "COLLECTIONS.h"
#include "IMAGE.h"

/*
The renderer is the class that is responsible for controlling the
draw process in the world. The renderer is responsible for all
Tile, Object, Player, and Actor render positions, as well as
texture information

updates required

-The inclusion of player, and actors in the draw processes
*/
class renderer
{
public:
	renderer(void);
	void addTile(int center[2], double color[3], int size);
	void render(void);
	void worldToArray(world gameSpace);
	void testRender(void);
	image getTileData(void);
	void changeTextureInfo(image newTextureData);
	actor animateActor(actor character, bool isMoving);
	player animatePlayer(player character, bool isMoving);

	void setUpActor(const char* statImage, actor character);
	void setUpPlayer(const char* startImage, player &character, world map);
	
	void setUpCharacters(unsigned int numberOfCharacters);
	
	~renderer(void);

private:
	
	int ** playerArray;
	double ** playerColors;

	int * vertices;
	double * colors;
	
	image tileData;
	image objectData;
	image *characterData;
	image playerData;

	vector<int*> tempVertices;
	vector<double*> tempColors;

	vector<int*> actorArrays;
	vector<double*> actorColors;

	/*BuildOk is used as a gaurd variable, so that if the
	arrays have already been written they won't rewrite
	when there are no changes*/
	bool buildOk;

	void printPoint(unsigned int pos);
	void clearArrays(void);

	void buildArrays();
	void addPoint(int point[2]);
	void addColor(double color[3]);

};

#endif