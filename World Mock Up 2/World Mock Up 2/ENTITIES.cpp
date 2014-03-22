/*
COPYRIGHT BENJAMIN ISHERWOOD 21/03/2014
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
#ifndef ENTITIES_METHODS
#define ENTITIES_METHODS

#include "ENTITIES.h"

unsigned int entity::getID(void) const {return ID;}
string entity::getDescription(void) const {return description;}
bool entity::getPassThrough(void) const{return passThrough;}

void entity::changePassThrough(bool passable) {passThrough = passable;}
void entity::changeID(unsigned int newID) {ID = newID;}
void entity::changeDescription(string newDescription) {description = newDescription;}

#endif