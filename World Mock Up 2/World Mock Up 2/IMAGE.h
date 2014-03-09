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
#ifndef _IMAGE_HANDLER
#define _IMAGE_HANDLER

#include "COLLECTIONS.h"

#ifndef TEXTURE_LOAD_ERROR
	#define TEXTURE_LOAD_ERROR 0
#endif

class image
{
	private: 
		bool imageAvailable;
		const char* imageName;
		int imageSize[2];
		//This is the image that we are using
		GLubyte *textureBinary;
		GLuint texture;
		//This is the texture being binded
		vector<double*> textureVector;
		//This also loads the images
		void checkIfAvailable(void);
		void buildTextureArray(void);
		void addTexture(double* textCoords);
		bool buildOkay;
		bool hasAlpha;

	public:
		

		image(void);
		image(const char* startImage);
		~image(void);
		double* getTextureArray(void);
		void setupTexture(void);
		void changeName(const char* name);
		void addTile(int ID);
		void writeReport(void);
		GLubyte* getTextureBinary(void);
		GLuint getTexture(void);
		double *textureArray;
		void addCharacter(void);
		void moveActorCoords(double pos[2]);
		void enableSetUp(void);
		void disableSetUp(void);
		char* getImageName(void);
};
#endif