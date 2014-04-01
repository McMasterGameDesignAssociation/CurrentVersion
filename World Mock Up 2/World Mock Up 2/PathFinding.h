/*
COPYRIGHT DON PHAM 01/04/2014
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
#ifndef _PATHFINDING
#define _PATHFINDING

#include "COLLECTIONS.h"

/* Todo:
 * 1) Change the openList type from list<node*> to a structure that can:
		. access minimum element and delete it
		. insertions many elements (4*pathlength or 8*pathlength for diagonals)
		. update and move certain element values in structure
	1.1) Possibly, if accessing the min element is O(1), change openList to not delete elements and just use node.closed(). This removes the
		  need for the closedList as we can now just clear the openList once done.

	2) Put node in its own .h and .cpp and make things private

	3) Create a structure in PathFinding.cpp to hold all unique booleans per actor ai. (currently at the top of NPCHandler.cpp)
		3.1) The same node map is then worked on directly for all pathfinding actor ai. 
			3.1a) So we can create a queue to work with one actor at a time.
			3.1b) Or to parallelize, for each actor's openList, make copies of just the nodes used (not the whole map) instead of using pointers.
	
	4) Initalize the pathfinding map inside World.cpp instead of NPCHandler.

	5) change node.adjacent from vector to node* array[8].
 */


/* // Possible better implementation openList
template<
	class T,
	class Container = std::vector<T>,
	class Compare = std::less<typename Container::value_type>
> class MyQueue : public std::priority_queue<T, Container, Compare>
	{
	public:
		typedef typename
			std::priority_queue<
			T,
			Container,
			Compare>::container_type::const_iterator const_iterator;

		const_iterator find(const T&val) const
		{
			auto first = this->c.cbegin();
			auto last = this->c.cend();
			while (first != last) {
				if (*first == val) return first;
				++first;
			}
			return last;
		}
		const_iterator bubbleUp(const T&val) const
		{
			auto first = this->c.cbegin();
			auto last = this->c.cend();
			while (first != last) {
				if (*first == val)
				{
					while (first != this->c.cbegin())
					{
						if (*(--first) > *first)
						{ // swap
							auto temp = first;
							--first = first;
							first = temp;
						}
						--first;
					}
					return;
				}
				++first;
			}
		}
};
	*/

class node
{
public:
	int tileID;
	int location[2];
	int h; // heuristic / estimated movement cost
	int g; // movement cost / actual distance cost
	int f; // f = g + h score
	node* parent[1];
	vector<node*> adjacent;
	bool visited;
	bool closed;

public:
	node(int id, int locations[2]) // constructor
	{
		tileID = id;
		location[0] = locations[0];
		location[1] = locations[1];
		h = 9999;
		g = 9999;
		f = 9999;
		visited = false;
		closed = false;
	}

	friend bool operator<(node &a, node &b) { return a.f < b.f ? true : false; }
};

class pathfinding
{
public:
	pathfinding(); // Initalize pathfinding 
	void generateMap(world*); // Generate a node map based of the tiles of the world.
	std::vector<node*> findPath(int startLocation[2], int targetLocation[2]);

private:
	void getAdjacentNodes(node* node); // takes a node and modify its node.adjancent vector
	std::vector<node*> createPath(node* end, node* start); // called from findPath after the final target node is found
};

#endif