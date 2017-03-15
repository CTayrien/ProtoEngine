/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "texture.h"

#include <FreeImage.h>
#include <GL\glew.h>

texture::texture(std::string filename)
{
	this->filename = filename;
}

texture::~texture()
{
}

bool texture::load()
{
	// Load
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(filename.c_str(), 0), filename.c_str());
	if (image == nullptr) 
		return false;

	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);

	// Generate and bind texture
	// declare a temp unsigned int
	glGenTextures(1, &id);				// use a temp unsigned int
	glBindTexture(GL_TEXTURE_2D, id);	// use a temp unsigned int

															// Upload to vram and clear ram
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(image32Bit), FreeImage_GetHeight(image32Bit), 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32Bit));
	FreeImage_Unload(image32Bit);

	// Set min filter to linear instead of mipmap linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void texture::use()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void texture::unload()
{
	glDeleteTextures(1, &id);
}
