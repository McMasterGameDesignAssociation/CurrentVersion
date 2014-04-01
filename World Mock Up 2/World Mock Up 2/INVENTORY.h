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
#ifndef INVENTORY_H
#define INVENTORY_H
class item;

#include "SYSTEMCOLLECTIONS.h"

/*
The inventory class is used to store vectors of items so that the
player maybe able to carry items and NPCs and objects can aswell
inventories will be used to define the win condition
*/
class inventory
{
private:
	vector<item*> currentInventory;
	unsigned int totalValue;
	unsigned int totalWhieght;

public:
	inventory(void);
	~inventory(void);
	//Check if the item is in the inventory
	bool checkItem(unsigned int ID);
	item removeItem(unsigned int ID);
	
	unsigned int getTotalWhieght(void) const;
	unsigned int getTotalValue(void) const;

	void addItem(item *newItem);
};

#endif