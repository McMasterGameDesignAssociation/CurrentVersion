/*
COPYRIGHT BENJAMIN ISHERWOOD 24/03/2014
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
#ifndef INVENTORY_METHODS
#define INVENTORY_METHODS

#include "INVENTORY.h"

inventory::inventory(void)
{
	totalValue = 0;
	totalWhieght = 0;
	currentInventory.clear();
}
/*
addItem takes an item as an input and checks to see if it is in the current
inventory, if the item is in the inventory increase the quantifer for that item
else push in an instance of the new item
*/
void inventory::addItem(item* newItem)
{
	unsigned int i;
	//Check if the item exists in the inventory already, if it does then break the loop
	//at the ID value of that item
	for(i = 0; i < currentInventory.size(); i++)
		if(currentInventory.at(i) -> getID() == newItem -> getID()) break;
	//If the item ID and the item ID of where the loop broke at are not the same
	//This means that the item exists outside of the current set, and therefore
	//The item needs to be added at the new position
	if(currentInventory.at(i) -> getID() != newItem -> getID()) 
		currentInventory.push_back(newItem);
	//Else increase the quantity of that item
	else currentInventory.at(i) -> increaseQuantity();
	totalValue += currentInventory.at(i) -> getValue();
	totalValue += currentInventory.at(i) -> getWhieght();
}

item inventory::removeItem(unsigned int removeID)
{
	unsigned int i;
	item temp;
	//Check to see if the value is inside the vector
	for(i = 0; i < currentInventory.size(); i++)
		if(currentInventory.at(i) -> getID() == removeID) break;
	//Check to see if the value found actually is the value and not just the end of the vector
	if(currentInventory.at(i) -> getID() == removeID)
	{
		temp = *currentInventory.at(i);
		//Reduce the wheight and the value of the inventory by the amount of the item
		totalWhieght -= currentInventory.at(i) -> getWhieght();
		totalValue -= currentInventory.at(i) -> getValue();
		//Remove 1 quantity from the item in the inventory, if the number is 0 then erase that
		//value for the the vector
		if(currentInventory.at(i) -> decreaseQuantity() < 1) currentInventory.erase(currentInventory.begin() + i);
	}
	return temp;
}
bool inventory::checkItem(unsigned int ID)
{
	for(unsigned int i = 0; i < currentInventory.size(); i++)
		if(currentInventory.at(i) -> getID() == ID) return true;
	return false;
}
unsigned int inventory::getTotalWhieght(void) const{return totalWhieght;}
unsigned int inventory::getTotalValue(void) const{return totalValue;}

inventory::~inventory(void) {currentInventory.clear();}
#endif