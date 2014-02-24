#ifndef _IMAGE_METHODS
#define _IMAGE_METHODS

#include "IMAGE.h"
image::image(void)
{
	imageAvailable = false;
	buildOkay = false;
	hasAlpha = false;
	imageName = new const char[1];
	imageSize[0] = 0, imageSize[1] = 0;
	textureBinary = NULL;
	glGenTextures(1, &texture);
}

image::image(const char* startImage)
{
	imageName = startImage;
	buildOkay = false;
	glGenTextures(1, &texture);
}

image::~image(void)
{
	glDeleteTextures(1, &texture);
	//imageName = NULL;
	//delete[] imageName;
	delete[] textureBinary;
	textureVector.clear();
}
void image::changeName(const char* name)
{
	imageName = name;
	checkIfAvailable();
}

void image::addTexture(double* textCoords)
{
	double* holdOver;
	holdOver = new double[2];
	holdOver[0] = textCoords[0];
	holdOver[1] = textCoords[1];
	textureVector.push_back(holdOver);
}

void image::addTile(int ID)
{
	//if(ID > setSize) return;
	double step;
	if(imageSize[0] > 0) step = double(imageSize[1])/double(imageSize[0]);
	else return;

	double temp[2];
	temp[0] = ID*step, temp[1] = 0;
	addTexture(temp);
	temp[0] = ID*step + step, temp[1] = 0;
	addTexture(temp);
	temp[0] = ID*step, temp[1] = 1;
	addTexture(temp);
	addTexture(temp);
	temp[0] = ID*step + step, temp[1] = 1;
	addTexture(temp);
	temp[0] = ID*step + step, temp[1] = 0;
	addTexture(temp);
}

void image::buildTextureArray(void)
{
	textureArray = new double[textureVector.size()*2];
	for(unsigned int i = 0; i < textureVector.size(); i++)
	{
		textureArray[i*2] = textureVector.at(i)[0];
		textureArray[i*2 + 1] = textureVector.at(i)[1];
	}
	buildOkay = false;
}

void image::checkIfAvailable(void) 
{
	png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;
	fopen_s(&fp, imageName, "rb");
    if (fp  == NULL)
	{
         imageAvailable = false;
		 return;
	}
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
										 NULL, NULL, NULL);
	if (png_ptr == NULL) 
	{
		fclose(fp);
		imageAvailable = false;
		return;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) 
	{
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		imageAvailable = false;
		return;
	}
	if (setjmp(png_jmpbuf(png_ptr))) 
	{
		/* Free all of the memory associated
		 * with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		/* If we get here, we had a
		 * problem reading the file */
		imageAvailable = false;
		return;
	}
 
	/* Set up the output control if
	 * you are using standard C streams */
	png_init_io(png_ptr, fp);

 	/* If we have already
	* read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 width, height;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
			 &interlace_type, NULL, NULL);
	imageSize[0] = width;
	imageSize[1] = height;
	(color_type == 6) ? hasAlpha = true : hasAlpha = false; 
	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	textureBinary = (unsigned char*) malloc(row_bytes * imageSize[1]+1);
 
	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
 
	for(int i = 0; i < height; i++) 
	{
		// note that png is ordered top to
		// bottom, but OpenGL expect it bottom to top
		// so the order or swapped
		memcpy(textureBinary+(row_bytes * (height-1-i)), row_pointers[i], row_bytes);
	}
 
	/* Clean up after the read,
	 * and free any memory allocated */
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
 
	/* Close the file */
	fclose(fp);
 
	/* That's it */
	imageAvailable = true;
	buildOkay = true;
}

void image::enableSetUp(void)
{
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	glBindTexture(GL_TEXTURE_2D, texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

void image::disableSetUp(void)
{
	glDisable(GL_BLEND | GL_SRC_ALPHA | GL_UNPACK_ALIGNMENT |
		GL_ONE_MINUS_SRC_ALPHA |  hasAlpha ? GL_RGBA : GL_RGB 
		| GL_UNSIGNED_BYTE | GL_TEXTURE_WRAP_S | GL_CLAMP |
		GL_TEXTURE_MAG_FILTER | GL_LINEAR | GL_TEXTURE_WRAP_T |
		GL_TEXTURE_MIN_FILTER);
}

void image::setupTexture(void)
{
 	if(!imageAvailable) checkIfAvailable();
	if(buildOkay)
	{
		buildTextureArray();
		writeReport();
	}
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageSize[0],
					 imageSize[1], 0, GL_RGBA, GL_UNSIGNED_BYTE,
					 textureBinary);
}

double* image::getTextureArray(void) {return textureArray;}

GLuint image::getTexture(void) {return texture;}

void image::writeReport(void)
{
	cout << "X size: " << imageSize[0] << " Y size: " << imageSize[1] << endl;
	cout << "Build okay? " << (buildOkay ? "True" : "False") << endl;
	cout << "Image exists? " << (imageAvailable ? "True" : "False") << endl;
}

void image::addCharacter(void)
{
	double temp[2];
	delete[] textureArray;

	textureArray = new double[12];

	temp[0] = 0, temp[1] = 0;
	addTexture(temp);
	temp[0] = .125, temp[1] = 0;
	addTexture(temp);
	temp[0] = 0, temp[1] = .25;
	addTexture(temp);
	addTexture(temp);
	temp[0] = .125, temp[1] = .25;
	addTexture(temp);
	temp[0] = .125, temp[1] = 0;
	addTexture(temp);
}

void image::moveActorCoords(double pos[2])
{
	textureArray[0]  = pos[0];
	textureArray[1]  = pos[1];
	textureArray[2]  = .125 + pos[0];
	textureArray[3]  = pos[1];
	textureArray[4]  = pos[0];
	textureArray[5]  = pos[1] + .25;
	textureArray[6]  = pos[0];
	textureArray[7]  = pos[1] + .25;
	textureArray[8]  = .125 + pos[0];
	textureArray[9]  = pos[1] + .25;
	textureArray[10] = .125 + pos[0];
	textureArray[11] = pos[1];
}
#endif