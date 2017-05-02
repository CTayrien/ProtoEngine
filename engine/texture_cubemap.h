/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "texture.h"
#include <vector>

class texture_cubemap :
	public texture
{
private:
	std::string filenames[6];

public:
	~texture_cubemap();

	texture_cubemap(std::string filenames[6]);
	bool load() override;
	void bind() override;
	void unload() override;
};