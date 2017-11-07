/*************************************************************************/
/*                          ImageLoader.cpp                              */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           Xenro Engine                                */
/*             https://github.com/Jmiller7023/Xenro-Engine               */
/*************************************************************************/
/*                 Copyright  11-3-2017 Joseph Miller.                   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "ErrorMessages.h"
#include <vector>

namespace Xenro {

GLTexture ImageLoader::loadPNG(std::string filePath) {
	//Generate GLTexture and set its fields to 0.
	GLTexture texture = {};
	
	//This is the input data to decodePNG, which we load from a file.
	std::vector<unsigned char> in;

	//This is the output data from decodePNG, which is the pixel data for out texture.
	std::vector<unsigned char> out;

	unsigned long height, width;

	//Read in the image file contents into a buffer.
	if (IOManager::readFileToBuffer(filePath, in) == false) {
		fatalError("Failed to read PNG to buffer from " + filePath);
	}

	//Decode the .png format into an array of pixels.
	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0) {
		fatalError("decodePNG failed with error code " + std::to_string(errorCode));
	}

	//Generate openGL texture object.
	glGenTextures(1, &texture.ID);

	//Bind the texture object.
	glBindTexture(GL_TEXTURE_2D, texture.ID);
	//Upload the pixels to the texture.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	//Set some texture parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//generates mipmaps.
	glGenerateMipmap(GL_TEXTURE_2D);

	//unbind the texture.
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;
	texture.filePath = filePath;

	//return a copy of the texture data.
	return texture;
	}
}