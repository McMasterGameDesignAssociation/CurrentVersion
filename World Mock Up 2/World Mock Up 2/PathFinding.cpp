#pragma once
#ifndef _PATHFINDING_METHODS
#define _PATHFINDING_METHODS

#include "PathFinding.h"
#include <list>

int mapX;
int mapY;
std::vector<vector<node>> nodeList;
world* theworld;

/* // alternate openList representation
struct OrderByNodeValue 
{
	bool operator() (node const &a, node const &b) { return a.f < b.f; }
};

//MyQueue<node, vector<node>, OrderByNodeValue> openList;
//priority_queue<node> openList;
*/

list<node*> openList;
list<node*> closedList; // need for now to reset nodes between different pathfindings

pathfinding::pathfinding()
{
	return;
}

void pathfinding::generateMap(world* world)
{
	theworld = world; // temp
	FileReader* gameFile = new FileReader("world.txt"); 
	std::vector<vector<int>> currentMap = gameFile->getMap(); //// !!!! currentMap doesnt read the first line of world.txt

	mapX = world->getX();
	mapY = world->getY();
	
	cout << "test pathfinding";

	nodeList.clear();

	/// Creating a node list
	for (int y = currentMap.size()-1; y >= 0; y--) // 
	{
		std::vector<node> tempvector;
		for (int x = 0; x < currentMap.at(0).size(); x++) // 
		{
			int location[2]; location[0] = x; location[1] = currentMap.size()-y-1; //currentMap.at(0).size()-y-1;

			if (x == 0 || y == 0 || y == currentMap.size() - 1 || x == currentMap.size() - 1)
			{
				tempvector.push_back(node(-1, location));
			}
			else 
			{
				tempvector.push_back(node(currentMap.at(y).at(x), location)); // passing tileID and tileLocation
				//cout << tempvector.at(j).f;
			}
		}
		nodeList.push_back(tempvector);
		tempvector.clear();
	}

	cout << "test pathfinding";
}


void pathfinding::getAdjacentNodes(node* currentNode)
{
	/// Returns the 8 adjacent tiles in an array*
	/// 012 -- 2
	/// 3x4 -- 1
	/// 567 -- 0

	//node* adjacent[8];

	int x = currentNode->location[0];
	int y = currentNode->location[1];
	//cout << x;
	//cout << y; 

	////////!!!!!!!!!!!!!!!!!!! THESE ARE WRONG I THINK
	currentNode->adjacent.push_back( &nodeList.at(y + 1).at(x - 1)); // diagonal
	currentNode->adjacent.push_back(&nodeList.at(y + 1).at(x)); // north
	currentNode->adjacent.push_back(&nodeList.at(y + 1).at(x + 1)); // diagonal
	currentNode->adjacent.push_back(&nodeList.at(y).at(x - 1)); // west
	currentNode->adjacent.push_back(&nodeList.at(y).at(x + 1)); // east
	currentNode->adjacent.push_back(&nodeList.at(y - 1).at(x - 1)); // diagonal
	currentNode->adjacent.push_back(&nodeList.at(y - 1).at(x)); // south
	currentNode->adjacent.push_back(&nodeList.at(y - 1).at(x + 1)); // diagonal

	//return *currentNode->adjacent;
}

std::vector<node*> pathfinding::findPath(int startLocation[2], int targetLocation[2]) // returns a node* path
{
	// pixels to coordinates
 
	int startX = floor(startLocation[0] / 64);
	int startY = floor(startLocation[1] / 64);
	int targetX = floor(targetLocation[0] / 64);
	int targetY = floor(targetLocation[1] / 64);

	node* startNode = &nodeList.at(startY).at(startX);

	// reset openList for next run
	std::list<node*>::const_iterator iterator;
	for (iterator = openList.begin(); iterator != openList.end(); ++iterator) {
		(*iterator)->f = 9999;
		(*iterator)->visited = false;
		(*iterator)->closed = false;
		(*iterator)->adjacent.clear();
	}
	openList.clear();

	// reset closedList for next run
	std::list<node*>::const_iterator iteratorC;
	for (iteratorC = closedList.begin(); iteratorC != closedList.end(); ++iteratorC) {
		(*iteratorC)->f = 9999;
		(*iteratorC)->visited = false;
		(*iteratorC)->closed = false;
		(*iteratorC)->adjacent.clear();
	}
	closedList.clear();


	// calculate starting node G score = 0
	startNode->g = 0;
	// calculate starting node h 
	startNode->h = abs(targetX - startX) + abs(targetY - startY);
	// calculate starting node f
	startNode->f = startNode->g+startNode->h;
	// reset parent value
	*startNode->parent = nullptr;
	
	openList.push_back(startNode);
	startNode->visited = true;

	// move curr node to closed list.

	// 1. push all unvisited adj to open list (min heap)
	//				calculate f
	// 2. pop min-key from heap
	// 3. get adj of min-key
	// 4. repeat from 1.

	// (2)
	while (!openList.empty())
	{
		/// Pick node with lowest f cost, remove it from openList
		//node* greedyPick = &openList.top();
		//openList.pop();

		node* greedyPick = openList.back();
		std::list<node*>::const_iterator greedyPickIndex = --openList.end();

		std::list<node*>::const_iterator iterator;
		for (iterator = openList.begin(); iterator != openList.end(); ++iterator) {
			if ((*iterator)->f < greedyPick->f)
			{
				greedyPick = *iterator;
				greedyPickIndex = iterator;
			}
		}

		closedList.push_back(greedyPick);
		openList.erase(greedyPickIndex);

		if (greedyPick->tileID == -1)
		{
			continue;
		}

		// if picked node == target location
		else if (greedyPick->location[0] == targetX && greedyPick->location[1] == targetY)
		{
			std::vector<node*> path = createPath(greedyPick, startNode); // create path backwards from here to start using parent
			return path;
		}
		else // if not at target yet
		{
			getAdjacentNodes(greedyPick);
			vector<node*> adj = (*greedyPick).adjacent;

			greedyPick->closed = true;
			// For each adjacent node, push to openList while calculating G
			for (int i = 0; i < 8; i++)
			{
				
			//	int test = (adj + 1)->location[0];
			//	test = adj[3].location[0];
			//	test = (adj + 3)->location[0];
				vector<node*> blah = greedyPick->adjacent;
				node* blah2 = blah.at(3);
			//	test =  (adj + 4)->location[0];
			//	test = (adj + 6)->location[0];
				// if in closed"List"
				if (adj.at(i)->closed == true)
				{
					continue;
				}
				// if no tile
				else if (&adj.at(i) == nullptr)
				{
					continue;
				}
				// if not walkable
				else if (theworld->getTileCollision(adj.at(i)->tileID) == false)
				{
					continue;
				}
				else if (i == 0 || i == 2 || i == 5 || i == 7) // !!! Can ignore DIAGONALS for speed
				{
					continue;
				}/**/
				else /// if walkable
				{
					// Calculate G score: (based off tile: ex/ mud tile = higher cost)
					int addedGCost = 0;
					if (abs(adj.at(i)->location[0] - greedyPick->location[0]) == 1 && abs(adj.at(i)->location[1] - greedyPick->location[1]) == 1)
					{
						addedGCost = 14;//cost of going to diagonal squares	
					}
					else
					{
						addedGCost = 10;//cost of going to non-diagonal squares	
					}
					int newG = greedyPick->g + addedGCost;

					// if not visited before or new score is better
					if (adj.at(i)->visited == false || newG < adj.at(i)->g)
					{
						/// => Possibly better path found
						adj.at(i)->parent[0] = greedyPick;
						adj.at(i)->h = 10 * abs(targetX - adj.at(i)->location[0]) + abs(targetY - adj.at(i)->location[1]);
						adj.at(i)->g = newG;
						adj.at(i)->f = adj.at(i)->h + adj.at(i)->g;
					}
					if (adj.at(i)->visited == false) {
						openList.push_back(adj.at(i));
						adj.at(i)->visited = true;
					}
					else
					{   /// has been visited
						/// Check if node still in correct position of openList
						// 1. remove element
						// 2. insert element in place

						// no correct place in a unsorted list
						continue;
					}
				}				
			}
		}
	} // while end


	// return closest Node instead if no path exists

	// temporary 
	vector<node*> justStartNode;
	justStartNode.push_back(startNode);
	return justStartNode;
}

std::vector<node*> pathfinding::createPath(node* end, node* start) // type array
{
	/// Using endNode.parent, we build the path backwards.

	node* curr = end;
	vector<node*> path; // path array
	int pathLength = 0;
	while (curr->parent != nullptr) {
		if (curr == nullptr) break;
		path.push_back(curr);
		pathLength++;
		curr = curr->parent[0];
	}
	cout << "pathLength:" + pathLength;
	return path;
}
#endif