/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include <string>
using std::string;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "asset.h"

class shader
	:public asset
{
public:
	string filenamev;
	string filenamef;
	uint32_t id = 0, vid = 0, fid = 0;

	shader(string filenamev, string filenamef);
	~shader();
	
	char* vshaderCode = nullptr;
	char* fshaderCode = nullptr;

	bool load() override;
	bool compile(GLenum shaderType);
	void use();
	void unload() override;
};