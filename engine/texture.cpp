/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "texture.h"

#include <FreeImage.h>
#include <GL\glew.h>
#include <iostream>

texture::texture(std::vector<std::string> filenames)
	:asset(filenames)
{
}

texture::~texture()
{
}

bool texture::load()
{
	// If already loaded, copy from asset map instead of loading again
	if (nullptr != assets[key]) {
		*this = *(texture*)(assets[key]);
		return true;
	}

	switch (filenames.size())
	{
		case 1:	loaded = load2dtexture();
			break;
		case 2*3: loaded = loadcubemap();
			break;
		default:loaded = false;
			break;
	}

	// Save a copy of this asset in the asset manager
	if (loaded) assets[key] = new texture(*this);

	return loaded;
}

bool texture::load2dtexture()
{
	// Allocate vram
	glGenTextures(1, &id);

	// Bind texture & set texture filters (Set min filter to linear instead of mipmap linear)
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Try open and get file type
	const char* file = filenames[0].c_str();
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

bool texture::loadcubemap()
{
	// Allocate vram for texture
	glGenTextures(1, &id);
	
	// Bind texture to cubemap binding point & set cubemap filters
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	// Load and upload six cubemap textures
	for (int i = 0; i < 6; i++)
	{
		// Read & process from HD
		FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(filenames[i].c_str(), 0), filenames[i].c_str());
		if (image == nullptr) return false;
		FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
		FreeImage_FlipVertical(image32Bit);		// Not sure why skybox images must be flipped. No uvs used in Skybox shader ... maybe it's a FreeImage thing? Maybe I should be asking the opposite, "Why do I not have to flip regular 2D textures? Do all of my models texture coordinates have 1-v where they should be v?"
	
		// Upload to 6 cubemap binding points: right, left (= left + 1), top (= left + 2), etc...
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
	
	// Unbind texture from cubemap binding point
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	
	loaded = true;
	
	return true;
}

void texture::unload()
{
	glDeleteTextures(1, &id);
	id = 0;
}