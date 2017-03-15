/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include <string>
using std::string;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class shader
{
public:
	string filenamev = "engine/shaders/vshader.glsl";
	string filenamef = "engine/shaders/fshader.glsl";

	uint32_t id = -1, vid = -1, fid = -1;

	shader();
	shader(string filenamev, string filenamef);
	~shader();
	
	bool load();
	bool compile(GLenum shaderType);
	bool use();
	void unload();
};