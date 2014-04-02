#pragma once
#ifndef _PATHFINDING_METHODS
#define _PATHFINDING_METHODS

#include "PathFinding.h"
#include <list>

bool setting_AllowDiagonals = true;

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
	theworld = world;
	FileReader* gameFile = new FileReader("world.txt"); 
	std::vector<vector<int>> currentMap = gameFile->getMap(); //// !!!! currentMap doesnt read the first line of world.txt

	mapX = world->getX();
	mapY = world->getY();
	
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
			}
		}
		nodeList.push_back(tempvector);
		tempvector.clear();
	}
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
	int startX = floor(startLocation[0] / theworld->getResolution());
	int startY = floor(startLocation[1] / theworld->getResolution());
	int targetX = floor(targetLocation[0] / theworld->getResolution());
	int targetY = floor(targetLocation[1] / theworld->getResolution());

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


	// calculate starting node scores
	startNode->g = 0;
	startNode->h = abs(targetX - startX) + abs(targetY - startY);
	startNode->f = startNode->g+startNode->h;
	*startNode->parent = nullptr; // reset parent value
	startNode->visited = true;
	
	openList.push_back(startNode);
	
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
				// if in closed List
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
				// if disallow diagonal movements
				else if (!setting_AllowDiagonals && (i == 0 || i == 2 || i == 5 || i == 7))
				{
					continue;
				}
				/// if walkable
				else 
				{
					// Calculate G score: (diagonal tiles cost "14", otherwise 10)
					int addedGCost = (abs(adj.at(i)->location[0] - greedyPick->location[0]) == 1 && abs(adj.at(i)->location[1] - greedyPick->location[1]) == 1) ? 14 : 10;
					// Later on we can add more costs for walking through different objects (like traps and other NPCs)
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

						// Our current openList implementation is unsorted...
						continue;
					}
				}				
			}
		}
	} // while end

	// If no path exists: return parital path instead.

	// temporary, return just the starting node.
	vector<node*> justStartNode;
	justStartNode.push_back(startNode);
	return justStartNode;
}

std::vector<node*> pathfinding::createPath(node* end, node* start) // type array
{
	/// Using endNode.parent, we build the path backwards.
	node* curr = end;
	vector<node*> path; // path array
	//int pathLength = 0;
	while (curr->parent != nullptr) {
		if (curr == nullptr) break;
		path.push_back(curr);
		//pathLength++;
		curr = curr->parent[0];
	}
	return path;
}
#endif