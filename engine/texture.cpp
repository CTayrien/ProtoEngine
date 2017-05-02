/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "texture.h"
#include "fileio.h"

#include <FreeImage.h>
#include <GL\glew.h>
#include <iostream>

texture::texture(std::string filename)
	:asset(filename)
{
}

texture::~texture()
{
}

bool texture::load()
{
	// Allocate vram
	glGenTextures(1, &id);

	// Bind texture & set texture filters (Set min filter to linear instead of mipmap linear)
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Try open and get file type
	const char* file = filename.c_str();
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file, 0);

	if (FIF_UNKNOWN == fif) {
		unload();
		glBindTexture(GL_TEXTURE_2D, 0);
		printf("\nError: Texture file path/type unknown: %s\n", file);
		return false;
	}

	// Read
	FIBITMAP* image = FreeImage_Load(fif, file);
	
	// Process
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	
	FreeImage_Unload(image);

	// Upload (ram->vram)
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_SRGB_ALPHA,
		FreeImage_GetWidth(image32Bit),
		FreeImage_GetHeight(image32Bit),
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32Bit));
	
	FreeImage_Unload(image32Bit);

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void texture::unload()
{
	glDeleteTextures(1, &id);
	id = 0;
}