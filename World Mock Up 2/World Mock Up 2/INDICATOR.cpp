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
#ifndef INDICATOR_BASE_METHODS
#define INDICATOR_BASE_METHODS

#include "INDICATOR.h"

int* indicator::getPosition(void) const {return position;}
int* indicator::getSize(void) const {return size;}
unsigned int indicator::getID(void) const {return ID;}
const char* indicator::getBitMapName(void) const{return bitmapName;}
void indicator::setBitmapName(const char* newName) {bitmapName = newName;}
void indicator::setSize(int* newSize) {size = newSize;}
void indicator::setPosition(int* newPosition) {position = newPosition;}
void indicator::changeID(unsigned int newID) {ID = newID;}
#endif