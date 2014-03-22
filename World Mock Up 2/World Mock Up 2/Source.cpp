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

/*
CURRENT VERSION ALPHA 0.05
VERSION NOTES
-Basic game operation (i.e. movement, basic collision detection)
-Basic file operation (i.e. fully readable files, no organization structure)
-Texturing
-Walk animations

-No level editor
-No win condition
-No lose condition
-No story elements

UPDATES REQUIRED

-Locking the mouse to the movement
	-An updated method will be need

-Lose condition needs to be added

-DTD, XML reader and conf reader needs to be implemented

*/

#pragma once
#ifndef _PURE_KLEPTOMANIA
#define _PURE_KLEPTOMANIA	"PURE KLEPTOMANIA"

#include "COLLECTIONS.h"
//#include "RENDERER.h"

using namespace std;

//Current values for maintaining the
//The size of the screen
int WIDTH = 600;
int HEIGHT = 600;

//This is the initial centering of the view port
//Set to 0,0 since the starting position needs to be
//decided by the current map
int viewPortCenter[2] = {0,0};

//These are just test constants and are pretty self
//explanatory
world DAN("world.txt");
player PLAYER_ONE(&DAN);
//bool suspicious = false;

/*
Added by Ryan and needs to be built
into its own class
*/

//NPC variables
/*int detectionRange = 64 * 100;
int frameCounter = 0;
int randomNumNPC;
int frameStop = 1000; //NPCs will update their direction in less frames if they hit a wall*/
//NPC variables

renderer scene;

#include "KEYBOARD.h"
using namespace kyb;

/*
contains:
player character
	character designates the player that the view port is following

Update viewport creates an invisible box around the player which gives
the area that the camera can see
*/
void updateViewPort(player* character)
{
	//The viewport encompasses 75% of the the center of the scene
	//Therefore when the chracter position reaches 25%> and <75%
	//The view port moves at the same speed as the character
	if((character -> getPosition()[0] - viewPortCenter[0]) > 0.75*WIDTH)
		viewPortCenter[0] += character -> getSpeed(); 
	else if((character -> getPosition()[0] - viewPortCenter[0]) < 0.25*WIDTH)
		viewPortCenter[0]-= character -> getSpeed(); 
	if((character -> getPosition()[1] - viewPortCenter[1]) > 0.75*HEIGHT)
		viewPortCenter[1]+= character -> getSpeed(); 
	else if((character -> getPosition()[1] - viewPortCenter[1]) < 0.25*HEIGHT)
		viewPortCenter[1]-= character -> getSpeed(); 
}

/*
Passive Mouse function that modifies the current hardcoded player information
and then passes it to the scene to render it
*/
void passiveMouse(int x, int y)
{
	int pos[] = {x, y};
	int dimensions[] = {WIDTH, HEIGHT};
	//PLAYER_ONE.followMouse(pos, dimensions);
	scene.animatePlayer(PLAYER_ONE, false);
}

/*
This is the obligatory display function, THE COMMENTS INSIDE
THE FUNCTION ARE IMPORTANT
*/
void display(void)
{
	//Obligatory Set up functions
	glClearColor(GLclampf(0),GLclampf(0),GLclampf(.2),GLclampf(0));
	glutInitDisplayMode(GL_DEPTH | GL_DOUBLE | GL_RGBA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//The Depth buffer is necessary for the transparencies to work
	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);

	//LoadIdentiry is used to clear all current transformations (only useful on start up
	//since all movement is done by modifiying the draw and not by using transisitions)
	glLoadIdentity();
	
	gluOrtho2D(viewPortCenter[0], WIDTH + viewPortCenter[0], viewPortCenter[1], HEIGHT + viewPortCenter[1]);
	glViewport(0,0,WIDTH, HEIGHT);

	//Update the view port to maintain the camera on the player
	updateViewPort(&PLAYER_ONE);

	//Never Forget the teture initialization
	scene.render();

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void reshape(int x, int y)
{
	WIDTH = x, HEIGHT = y;
	updateViewPort(&PLAYER_ONE);
}

void idle(void)
{
	if(!pause && (DAN.getFrameCounter() == DAN.getFrameStop()))
	{
		PLAYER_ONE.setSpeed(8);
		menuStates(PLAYER_ONE, &DAN, &scene);
		//Added by Ryan
		DAN.updateNPCSet(&PLAYER_ONE, &scene); // This is the NPC idler (it works :D)
	}
	else if(numberSeries.size() < 1000)makeRandomNumber(DAN.getFrameCounter());
	else for(int i = 0; i < getRandomNumber()%1000; i++) numberSeries.pop();
	DAN.updateWorldClock();
}

/*
Populate world reads in unformatted files and populates the current
game world

Required Updates:
-The file reader should be able to handle structured
file types, specifically in 
	-XML(This will be used for data transmission of hard coded entities)
	-DTD(This is the key file that explains to the reader
	which information belongs to which class and how to handle it)
	-CONF(This will be used for the dynamic information such as 
	gamefiles, world files, object files etc.)
	-PNG(This will be used to store images)

-If time permits there should be an update added so that 
files are stored as Byte information and not as plaintext
as to allow a 4 bit shift to each character to make the file
unreadable outside of the game program

*/

/*
Obligatory main function

This requires a lot of clean up

argc == argument count
argv == argument vector
*/
void main(int argc, char* argv[])
{
		resetKeys();

		/*(+) NPC stuff 
		*This will initialize all the actors and push them into DAN.actorSet
		*/
		for (int i = 0; i < 40; i++)
		{	
			actor newActor(64*5,5*64, 8, "test_subject_2.png", randomMovement, &DAN);
			DAN.addActor(newActor);
		}
		for (int i = 0; i < 1; i++)
		{	
			actor newActor(7*64,13*64, 4, "Charactersforreal.png",  randomMovement, &DAN);
			DAN.addActor(newActor);
		}
		for (int i = 0; i < 10; i++)
		{	
			actor newActor(64*6,5*64, 8, "test_subject_3.png", randomMovement, &DAN);
			DAN.addActor(newActor);
		}
		//(-) NPC stuff //

        tile block;
        object newBlock;

        unsigned int size[] = {5,5};

        DAN.changePlayerStart(size);
        player greg(&DAN);
        PLAYER_ONE = greg;

        block.changeDescription("HOORAY");
		DAN.addTile(block);
		block.changeDescription("NOT HOORAY");
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		block.changePassThrough(true);
		DAN.addTile(block);
		block.changePassThrough(false);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
        //DAN.printLog();

        DAN.populateWorld();
		scene.setUpPlayer("Charactersforreal.png", PLAYER_ONE, &DAN);
		scene.worldToArray(&DAN);	
		scene.setupActorArrays(&DAN);

        glutInit(&argc, argv);
        glutInitWindowSize(600,600);
		glutCreateWindow(_PURE_KLEPTOMANIA);
		//Glew has to be initialized on a window for window basiss
		//glewInit();
        
		glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboardInput);
		glutPassiveMotionFunc(passiveMouse);
        glutKeyboardUpFunc(keyRelease);
		glutSpecialFunc(movementInput);
		glutSpecialUpFunc(movementRelease);
        glutMainLoop();
}
#endif