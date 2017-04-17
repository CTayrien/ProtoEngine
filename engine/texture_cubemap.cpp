/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "texture_cubemap.h"
#include "fileio.h"

#include <FreeImage.h>
#include <GL\glew.h>

texture_cubemap::~texture_cubemap()
{
}

// Right, Left, Top, Bottom, Back, Front
texture_cubemap::texture_cubemap(std::string filenames[6])
	:texture(filenames[0])
{
	this->filenames[0] = filenames[0];
	this->filenames[1] = filenames[1];
	this->filenames[2] = filenames[2];
	this->filenames[3] = filenames[3];
	this->filenames[4] = filenames[4];
	this->filenames[5] = filenames[5];
}

void texture_cubemap::load()
{
	// Allocate tex in vram
	glGenTextures(1, &id);

	// Bind & set filters
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Load and upload
	for (int i = 0; i < 6; i++)
	{
		// Read & process from HD
		FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(filenames[i].c_str(), 0), filenames[i].c_str());
		FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
		FreeImage_FlipVertical(image32Bit);

		// Upload
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_SRGB_ALPHA, 
			FreeImage_GetWidth(image32Bit),
			FreeImage_GetHeight(image32Bit),
			0,
			GL_BGRA, 
			GL_UNSIGNED_BYTE,
			(void*)FreeImage_GetBits(image32Bit));

		// Clear ram
		FreeImage_Unload(image32Bit);
		FreeImage_Unload(image);
	}

	// Unbind
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	loaded = true;
}

void texture_cubemap::use()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void texture_cubemap::unload()
{
	glDeleteTextures(1, &id);
}