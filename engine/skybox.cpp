/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "skybox.h"
#include "engine.h"
#include "texture_cubemap.h"

skybox::skybox()
{
	tag = "skybox";
	mod = new model("engine/models/skybox2.dat");
	
	// Space-scape skybox images given out of order. If order changed to expected, seams don't line up, regardless of flipping images vert & horiz. There was no "OpenGL" export option so I chose Ogre3D - bad choice? Perhaps -z is not forward in that engine, so the names understood to refer to +/- z are swapped. After checking http://www.ogre3d.org/forums/viewtopic.php?t=18856, it seems that Ogre3D is OpenGL-like (right handed, -z into screen). Unity is +z into screen. unreal is +z up. 3ds max is +z up. Maybe spacespace names them back and front because they assume +z is the front? who knows.
	std::string filenames[6] = {
		"engine/textures/spacescape/spacescape_right1.png",
		"engine/textures/spacescape/spacescape_left2.png",
		"engine/textures/spacescape/spacescape_top3.png",
		"engine/textures/spacescape/spacescape_bottom4.png",
		"engine/textures/spacescape/spacescape_front5.png",		//expected: back
		"engine/textures/spacescape/spacescape_back6.png"		//expected: front
	};

	tex = new texture_cubemap(filenames);
}

skybox::~skybox()
{
	delete mod;
	delete tex;
}

void skybox::script()
{
	// skybox has no behavior
}

void skybox::render()
{
	// Render first
	engine::shader_skybox.use();
	glDisable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_CUBE_MAP, tex->id);
	glBindVertexArray(mod->vao);
	glDrawArrays(GL_TRIANGLES, 0, mod->nverts);

	glEnable(GL_DEPTH_TEST);
	engine::shader_pblinn.use();
}