/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "texture.h"
#include "fileio.h"

#include <FreeImage.h>
#include <GL\glew.h>

texture::texture(std::string filename)
{
	this->filename = filename;
}

texture::~texture()
{
}

void texture::load()
{
	// Read & process
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(filename.c_str(), 0), filename.c_str());
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	
	// Allocate vram
	glGenTextures(1, &id);

	// Bind texture & set texture filters (Set min filter to linear instead of mipmap linear)
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Upload to vram
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_SRGB_ALPHA,
		FreeImage_GetWidth(image32Bit),
		FreeImage_GetHeight(image32Bit),
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32Bit));
	
	// Clear ram
	FreeImage_Unload(image);
	FreeImage_Unload(image32Bit);

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	loaded = true;
}

void texture::use()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void texture::unload()
{
	glDeleteTextures(1, &id);
	id = 0;
}
