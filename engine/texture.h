/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include <string>

class texture
{
private:
	std::string filename;
	uint32_t id = 0;
public:
	texture(std::string filename);
	~texture();

	void load();
	bool loaded = false;

	void use();

	void unload();
};