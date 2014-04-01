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
#ifndef GUI_METHODS
#define GUI_METHODS

#include "GUI.h"

gui::gui(void)
{
	textInterface.clear();
	floatInterface.clear();
	integerInterface.clear();
}

void gui::addTextInterface(stringIndicator newInterface)
{
	newInterface.changeID(textInterface.size());
	textInterface.push_back(newInterface);
}

void gui::addFloatInterface(doubleIndicator newInterface)
{
	newInterface.changeID(floatInterface.size());
	floatInterface.push_back(newInterface);
}

void gui::addIntegerInterface(longIndicator newInterface)
{
	newInterface.changeID(integerInterface.size());
	integerInterface.push_back(newInterface);
}
#endif