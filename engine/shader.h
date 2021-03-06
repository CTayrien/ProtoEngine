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
	uint32_t id = 0, sids[2];

	shader();
	shader(std::string filenamev, std::string filenamef);
	~shader();

	bool load() override;
	void use();
	void unload() override;
};