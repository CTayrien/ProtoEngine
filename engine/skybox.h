/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"
#include "shader.h"

class skybox
	: public object
{
private:
public:
	shader skybox_shader = shader(
		std::string("engine/shaders/vshader_skybox.glsl"),
		std::string("engine/shaders/fshader_skybox.glsl"));

	skybox();
	~skybox();

	bool load() override;
	bool loaded() override;
	void unload() override;

	void script() override;
	void render() override;
};