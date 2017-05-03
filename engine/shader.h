/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include <string>

#include <GL/glew.h>
#include "asset.h"

class shader
	:public asset
{
public:
	std::string filenames[2];
	
	uint32_t id = 0, ids[2];

	shader(std::string filenamev, std::string filenamef);
	~shader();
	
	char* vshaderCode = nullptr;
	char* fshaderCode = nullptr;

	bool load() override;
	void use();
	void unload() override;
};