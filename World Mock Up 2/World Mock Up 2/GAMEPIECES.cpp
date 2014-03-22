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
#ifndef GAMEPIECES_METHOD
#define GAMEPIECES_METHOD

#include "GAMEPIECES.h"

direction gamepiece::getFace(void) const{return face;}
unsigned int* gamepiece::getPosition(void) const{return position;}
const char* gamepiece::getBitMapName(void) const{return bitMapName;}

void gamepiece::changePosition(unsigned int pos[2]) {position[0] = pos[0], position[1] = pos[1];}
void gamepiece::changeBitMap(const char* newBitMap) {bitMapName = newBitMap;}
void gamepiece::setDirection(direction newFace) {face = newFace;}
void gamepiece::incrementDirection(void) {face++;}
void gamepiece::decrementDirection(void) {face--;}
void gamepiece::updatePosition(void) 
{
	vertices[0]  = position[0] - (size/2), vertices[1]  = position[1] - (size/2),
	vertices[2]  = position[0] + (size/2), vertices[3]  = position[1] - (size/2),
	vertices[4]  = position[0] - (size/2), vertices[5]  = position[1] + (size/2),
	vertices[6]  = position[0] - (size/2), vertices[7]  = position[1] + (size/2),
	vertices[8]  = position[0] + (size/2), vertices[9]  = position[1] + (size/2),
	vertices[10] = position[0] + (size/2), vertices[11] = position[1] - (size/2);

	for(int i = 0; i < 18; i++) shadeVertices[i] = 1;
}

#endif