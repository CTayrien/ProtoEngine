/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include <string>

class texture
{
protected:
	std::string filename;
	uint32_t id = 0;
public:
	texture(std::string filename);
	virtual ~texture();

	virtual void load();
	bool loaded = false;

	virtual void bind();

	virtual void unload();
};