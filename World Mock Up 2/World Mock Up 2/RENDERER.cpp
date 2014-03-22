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
#ifndef _RENDERER_METHODS
#define _RENDERER_METHODS

#include "RENDERER.h"
//#include "IMAGE.h"
/*
renderer destructor

Clears
-tile vertices
-tile colorss
-player vertices
-player color data
-all of the temporary vectors

*/
renderer::~renderer(void)
{
	delete[] tileArray;
	delete[] tileColors;
	//delete[] playerArray;
	tempColors.clear();
	tempVertices.clear();
}

/*
ClearArrays clears all of the tile information
and then sets the renderer the ability to build
to true
*/
void renderer::clearArrays(void)
{
	delete[] tileArray;
	delete[] tileColors;
}

/*
Obligatory empty constructor, clears all of the vectors, and
sets all of the arrays to zero dimensional arrays

updates required
-The hard coded image needs to be user defined
-
*/
renderer::renderer(void)
{
	number_of_tiles = 0;
	//This clears the arrays
	clearArrays();
	
	tempVertices.clear();
	tempColors.clear();
	//This needs to be user selected, or an agreed upon
	//null image needs to be made
	tileData = new image[1];
	tileData -> changeName("tile_set_1.png");
	
	playerData = new image[1];
	playerData -> addCharacter();
	//playerData.setupTexture();
	//Initialize the image binary to a 0
	//dimensional array to avoid memory issues
	//characterData = new image[50];

	/*Player data will always be in 6 doubles
	and 6 triples (2 triangles, not in strips).
	So this is a valid to always set the size
	of the player character, if two player is implemented
	revision will be needed to handle an array of player
	arrays*/
	playerArray = new int*[12];
	playerColors = new double*[18];
	int temp = 1;
	for(int i = 0; i < 18; i++) playerArray[i] = &temp;
	//for(int i = 0; i < 18; i++) playerColors[i] = &dTemp;

	/*Object Data, and NPC data needs to be added to this function*/
	buildOk = true;
}

/*
Build arrays sets up the arrays that hold all of the draw information
Arrays are only built if two conditions are met, the first of which is 
ther has been a change to the current world information and the second
is there needs to be available world information to be written

Updates required
-Addition of character arrays
-Addition of object arrays

*/
void renderer::buildArrays(void)
{
	if(!tempVertices.empty())
	{
		clearArrays();
		tileArray = new int[tempVertices.size()*2];
		tileColors = new double[tempColors.size()*3];
		for(unsigned int i = 0; i < tempVertices.size(); i++)
		{
			tileArray[i*2] = tempVertices.at(i)[0];
			tileArray[i*2 + 1] = tempVertices.at(i)[1];
			tileColors[i*3] = tempColors.at(i)[0];
			tileColors[i*3 + 1] = tempColors.at(i)[1];
			tileColors[i*3 + 2] = tempColors.at(i)[2];
		}
		//This line indicates that all of the current world is
		//up-to-date and is not needed to be recalculated
		buildOk = false;
	}
	number_of_tiles = tempVertices.size();
	tempColors.clear();
	tempVertices.clear();
}

/*
addPoint adds in a single tile to the temporary vertices
as an x and y coordinate as a center point

updates required
-Sorting needs to be added so that the draw doesn't get confused
-Add Character and add object needs to be added into this aswell
since add point is currently only able to add tile information

*/
void renderer::addPoint(int point[2]) 
{
	buildOk = true;
	int* newPoint;
	newPoint = new int[2];
	newPoint[0] = point[0], newPoint[1] = point[1];
	tempVertices.push_back(newPoint);
}

/*
addPoint adds in a single tile color to the temporary colors
as an rgb color selection, where the color corresponds to the
index of the temporary vertices

updates required
-Sorting needs to be added so that the draw doesn't get confused
-Add Character and add object needs to be added into this aswell
since add point is currently only able to add tile information
*/
void renderer::addColor(double color[3]) 
{
	buildOk = true;
	double* newColor;
	newColor = new double[3];
	newColor[0] = color[0], newColor[1] = color[1], newColor[2] = color[2];
	tempColors.push_back(newColor);
}

/*
addTile builds a set of vertices that make up two triangles
*/
void renderer::addTile(int center[2], double color[3], int size)
{
	for(int i = 0; i < 6; i++) addColor(color);
	int point[2];
	point[0] = center[0] - size/2, point[1] = center[1] - size/2;
	addPoint(point);
	point[0] = center[0] + size/2, point[1] = center[1] - size/2;
	addPoint(point);
	point[0] = center[0] - size/2, point[1] = center[1] + size/2;
	addPoint(point);
	point[0] = center[0] - size/2, point[1] = center[1] + size/2;
	addPoint(point);
	point[0] = center[0] + size/2, point[1] = center[1] + size/2;
	addPoint(point);
	point[0] = center[0] + size/2, point[1] = center[1] - size/2;
	addPoint(point);
}

/*
	render takes all of the arrays that are contained in the render class
	and builds the draw arrays that will be used to manage all of the
	graphics on the screen
*/
void renderer::render(void)
{
	bool check = false;
	if(buildOk) buildArrays();

	//Enable clientStates so that the drawArrays has
	//the correct array information
	//Vertex is for the spacial information
	//Color is for the shading of the object (when no texture is
	//available the color is very visible
	//Texture is for the image information
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//Image Data for character Texture is not
	//Actually set up in the system, this needs
	//To be investigated
	glEnable(GL_TEXTURE_2D);

	tileData -> setupTexture();
	tileData -> enableSetUp();

	glVertexPointer(2, GL_INT, 0, tileArray);
	glColorPointer(3, GL_DOUBLE, 0, tileColors);
	glTexCoordPointer(2, GL_DOUBLE, 0, tileData -> textureArray);
	glDrawArrays(GL_TRIANGLES, 0, number_of_tiles);
	tileData -> disableSetUp();

	glClear(GL_DEPTH_BUFFER_BIT);
	playerData -> setupTexture();
	playerData -> enableSetUp();

	glVertexPointer(2, GL_INT, 0, *playerArray);
	glColorPointer(3, GL_DOUBLE, 0, *playerColors);
	glTexCoordPointer(2, GL_DOUBLE, 0, playerData -> textureArray);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	playerData -> disableSetUp();

	glClear(GL_DEPTH_BUFFER_BIT);
	for(unsigned int i = 0; i < actorArrays.size(); i++)
	{
		if( i == 0 || (i > 0 && characterData[i].getImageName() != characterData[i-1].getImageName()))
		{
			characterData[i].setupTexture();
			characterData[i].enableSetUp();
			check = true;
		}
		glVertexPointer(2, GL_INT, 0, *actorArrays.at(i));
		glColorPointer(3, GL_DOUBLE, 0, *actorColors.at(i));
		glTexCoordPointer(2, GL_DOUBLE, 0, characterData[i].textureArray);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		if(check) 
		{
			characterData[i].disableSetUp();
			check = false;
		}
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

image renderer::getTileData(void) {return *tileData;}
void renderer::changeTextureInfo(image newTextureData) {tileData = &newTextureData;}

void renderer::printPoint(unsigned int pos)
{
	if(pos < tempVertices.size()) cout << tempVertices.at(pos)[0] << " x pos" 
		<< endl << tempVertices.at(pos)[1] << " y pos" << endl;
	else cout << "no point found" << endl;
}

void renderer::setupActorArrays(world* map)
{
	characterData = new image[map -> actorSet.size()];
	for(unsigned int i = 0; i < map -> actorSet.size(); i++)
	{
		actorArrays.push_back(new int*[12]);
		actorColors.push_back(new double*[18]);
		setUpActor(map -> actorSet.at(i).getBitMapName(), &(map -> actorSet.at(i)));
	}
}

void renderer::worldToArray(world* gameSpace)
{
	unsigned int pos[2];
	double color[] = {1,1,1};
	int location[2];
	for(int i = 0; i < gameSpace -> getY(); i++)
	{
		pos[1] = i;
		for(int j = 0; j < gameSpace -> getX(); j++)
		{
			pos[0] = j;
			tileData -> addTile(gameSpace -> checkTileMap(pos)); 
			location[0] = j*gameSpace -> getResolution(), 
				location[1] = i*gameSpace -> getResolution();
			addTile(location, color, gameSpace -> getResolution());
		}
	}
}


void renderer::setUpActor(const char* startImage, actor* character)
{
	characterData[character -> getID()].changeName(startImage);
	characterData[character -> getID()].addCharacter();
	actorColors.at(character -> getID()) = new double*[18];
	for(int i = 0; i < 12; i++) actorArrays.at(character -> getID())[i] = &character -> vertices[i];
	for(int i = 0; i < 18; i++)  actorColors.at(character -> getID())[i] = &character -> shadeVertices[i];
}

void renderer::setUpPlayer(const char* startImage, player &character, world* map)
{
	playerData -> changeName(startImage);
	playerData -> addCharacter();
	for(int i = 0; i < 12; i++) playerArray[i]  = &character.vertices[i];
	for(int i = 0; i < 18; i++)  playerColors[i] = &character.shadeVertices[i];
}

void renderer::animatePlayer(player &character, bool isMoving)
{
	double temp[2];
	(character.getAnimationStep() > 6) ? character.setAnimationStep(0) : 0;
	switch(character.getFace())
	{
		case Up: 
		case UpRight: 
		case UpLeft: 
			temp[1] = .25;
			break;
		case Left: temp[1] = 0;
			break;
		case Down:
		case DownRight:
		case DownLeft: temp[1] = .75;
			break;
		case Right: temp[1] = .5;
			break;
		default:
			break;
	}
	temp[0] = double(character.getAnimationStep())*.125;
	if(isMoving) character.incAnimationStep();
	playerData -> moveActorCoords(temp);
}

void renderer::animateActor(actor &character, bool isMoving)
{
	double temp[2];
	(character.getAnimationStep() > 6) ? character.setAnimationStep(0) : 0;
	switch(character.getFace())
	{
		case Up: 
		case UpRight: 
		case UpLeft: 
			temp[1] = .25;
			break;
		case Left: temp[1] = 0;
			break;
		case Down:
		case DownRight:
		case DownLeft: temp[1] = .75;
			break;
		case Right: temp[1] = .5;
			break;
		default:
			break;
	}
	temp[0] = double(character.getAnimationStep())*.125;
		if(isMoving) character.incAnimationStep();
	characterData[character.getID()].moveActorCoords(temp);
}
#endif