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
		"engine/textures/skybox/right.jpg",
		"engine/textures/skybox/left.jpg",
		"engine/textures/skybox/top.jpg",
		"engine/textures/skybox/bottom.jpg",
		"engine/textures/skybox/back.jpg",
		"engine/textures/skybox/front.jpg"
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
	// Or should I move the camera to the box, render, and move it back?
	//tform.loc = engine::cam.tform.loc;
	
	//tform.update();
}

void skybox::render()
{
	// special settings (use special material)

	object::render();

	// unuse shader
}

void skybox::stop()
{
	mod->unload();
	tex->unload();
	// shader unload
}