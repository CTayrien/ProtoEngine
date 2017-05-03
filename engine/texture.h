/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include <string>
#include "asset.h"

class texture
	:public asset
{
public:
	uint32_t id = 0;
	
	texture(std::string filename);
	virtual ~texture();

	virtual bool load() override;

	virtual void unload() override;
};