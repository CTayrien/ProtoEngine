/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "skybox.h"
#include "engine.h"
#include "texture_cubemap.h"

skybox::skybox()
{
	tag = "skybox";
	mod = new model("engine/models/skybox.dat");

	std::string filenames[6] = {
		"engine/textures/spacescape_right1.png",
		"engine/textures/spacescape_left2.png",
		"engine/textures/spacescape_top3.png",
		"engine/textures/spacescape_bottom4.png",
		"engine/textures/spacescape_back6.png",
		"engine/textures/spacescape_front5.png"
	};
	tex = new texture_cubemap(filenames);
}

skybox::~skybox()
{
	delete mod;
	delete tex;
}

bool skybox::start()
{
	mod->load();
	if (!mod->loaded) return false;

	tex->load();
	if (!tex->loaded) return false;
	
	return true;
}

void skybox::update()
{
	
}

void skybox::render()
{
	renderer::shader_skybox.use();

	// Skybox shader & uniform
	glm::vec3 temp = engine::cam.tform.loc;
	engine::cam.tform.loc = glm::vec3();
	engine::cam.upload();
	engine::cam.tform.loc = temp;

	// Using a special model will remedy the need for toggling cull face. The model does not need uvs and normals. A special model loader will support that.
	glDisable(GL_CULL_FACE);
	object::render();
	glEnable(GL_CULL_FACE);
	
	glClear(GL_DEPTH_BUFFER_BIT);

	renderer::theshader.use();
}

void skybox::stop()
{
	mod->unload();
	tex->unload();
}