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
#pragma once

#ifndef _RENDERER
#define _RENDERER

#include "COLLECTIONS.h"

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
	void worldToArray(world* gameSpace);
	void testRender(void);
	image getTileData(void);
	void changeTextureInfo(image newTextureData);
	void animateActor(actor &character, bool isMoving);
	void animatePlayer(player &character, bool isMoving);

	void setUpActor(const char* startImage, actor* character);
	void setUpPlayer(const char* startImage, player &character, world* map);

	void setupActorArrays(world* map);
	
	~renderer(void);

private:
	
	int number_of_tiles;
	int ** playerArray;
	double ** playerColors;

	int * tileArray;
	double * tileColors;
	
	//All image data needs to be used as pointers
	image *characterData;
	image *tileData;
	image *objectData;
	image *playerData;

	vector<int*> tempVertices;
	vector<double*> tempColors;

	vector<int**> actorArrays;
	vector<double**> actorColors;

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