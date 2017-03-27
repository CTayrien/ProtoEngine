/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "skybox.h"
#include "engine.h"

skybox::skybox()
{
	tag = "skybox";
	mat = material(1, 0, 0, 1);
	mod = new model("engine/models/skybox.obj");
	tex = new texture("engine/textures/skybox.png");
}

skybox::~skybox()
{
	delete mod;
	delete tex;
}

bool skybox::start()
{
	if (!mod->load())
		return false;

	if (!tex->load())
		return false;
	
	return true;
}

void skybox::update()
{
	// Or should I move the camera to the box, render, and move it back?
	tform.loc = engine::cam.tform.loc;
	
	tform.update();
}

void skybox::render()
{
	// special settings (use special material)
	mat.use();
	glDisable(GL_CULL_FACE);

	object::render();

	glEnable(GL_CULL_FACE);
	renderer::thematerial.use();
	glClear(GL_DEPTH_BUFFER_BIT);
}

void skybox::stop()
{
	mod->unload();
	tex->unload();
}