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
#ifndef _KEYBOARD_MACHINE
#define _KEYBOARD_MACHINE

#include "COLLECTIONS.h"

namespace kyb
{

	/****

	0 - W
	1 - S
	2 - A
	3 - D
	4 - Action/E
	5 - Inventory/Q
	6 - Run/Walk/Shift
	7 - MainMenu/ESC

	***/
	bool keys[8];
	bool pause = false;
	/* This will be the clear keys function */
	static void resetKeys(void) {for(int i = 0; i < 8; i++) keys[i] = false;}
	static void movementInput(int key, int x, int y)
	{
		switch(key)
		{
		case GLUT_KEY_UP: keys[0] = true;
			keys[1] = false;
			break;

		case GLUT_KEY_DOWN: keys[0] = false;
			keys[1] = true;
			break;

		case GLUT_KEY_LEFT: keys[2] = true;
			keys[3] = false;
			break;

		case GLUT_KEY_RIGHT: keys[2] = false;
			keys[3] = true;
			break;
		default: break;
		}
	}
	static void movementRelease(int key, int x, int y)
	{
		switch(key)
		{
		case GLUT_KEY_UP: keys[0] = false;
			break;

		case GLUT_KEY_DOWN: keys[1] = false;
			break;

		case GLUT_KEY_LEFT: keys[2] = false;
			break;

		case GLUT_KEY_RIGHT: keys[3] = false;
			break;
		default: break;
		}
	}
	static void keyRelease(unsigned char keyStroke, int x, int y)
	{
		unsigned int pos[] = {5, 17};
		switch(keyStroke)
		{
		case 'e': 
		case 'q': 
		default:
			break;
		}
	}

	/*

	Basic input for the keyboard

	*/
	static void keyboardInput(unsigned char keyStroke, int x, int y)
	{
		unsigned int pos[] = {5, 14};
		switch(keyStroke)
		{
		case 'e': resetKeys();
			keys[4] = true;
			break;

		case 'q': resetKeys();
			keys[5] = true;
			break;
		case 'p': pause = !pause;
		default: break;
		}
	}

	/* This is the state machine to run the keyboard in the idleFunc */
	static void menuStates(player &character, world *map, renderer *currentScene)
	{
		//W and A
		if(keys[0] && keys[2])
		{
			if(keys[6]);
			else 
			{
				character.checkMovement(map, 0, 1);
				character.checkMovement(map, -1, 0);
				character.setDirection(Left);
				currentScene -> animatePlayer(character, true);
			}
		}
		//W and D
		else if(keys[0] && keys[3])
		{
			if(keys[6]);
			else
			{
				character.checkMovement(map, 0, 1);
				character.checkMovement(map, 1, 0);
				character.setDirection(Right);
				currentScene -> animatePlayer(character, true);
			}
		}
		//S and A
		else if(keys[1] && keys[2])
		{
			if(keys[6]);
			else 
			{
				character.checkMovement(map, -1, 0);
				character.checkMovement(map, 0, -1);
				character.setDirection(Left);
				currentScene -> animatePlayer(character, true);
			}

		}
		//S and D
		else if(keys[1] && keys[3])
		{
			if(keys[6]);
			else 
			{
				character.checkMovement(map, 1, 0);
				character.checkMovement(map, 0, -1);
				character.setDirection(Right);
				currentScene -> animatePlayer(character, true);
			}

		}
		//W
		else if(keys[0])
		{
			if(keys[6]);
			else 
			{
				character.checkMovement(map, 0, 1);
				character.setDirection(Up);
				currentScene -> animatePlayer(character, true);
			}
		}
		//S
		else if(keys[1])
		{
			if(keys[6]);
			else 
			{ 
				character.checkMovement(map, 0, -1);
				character.setDirection(Down);
				currentScene -> animatePlayer(character, true);
			}
		}
		//A
		else if(keys[2])
		{
			if(keys[6]);
			else 
			{
				character.checkMovement(map, -1, 0);
				character.setDirection(Left);
				currentScene -> animatePlayer(character, true);
			}
		}
		//D
		else if(keys[3])
		{
			if(keys[6]);
			else 
			{
				character.checkMovement(map, 1, 0);
				character.setDirection(Right);
				currentScene -> animatePlayer(character, true);
			}
		}
		//Action or E key
		//else if(keys[4]) ;
		//Menu or Q key
		else if(keys[5]) 
		{
		_CrtDumpMemoryLeaks();
		exit(0);
		}
	}
}
#endif