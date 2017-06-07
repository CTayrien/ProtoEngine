/* Wrecksite: free open-source prototype sci-fi exploration game in ethereal space.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "wrecksite.h"
#include "engine.h"

#include <iostream>

object *wreck;

class ether : public object {
public:
	glm::vec3 sway;
	glm::vec3 axis = { 1, 0, 0 };
	float period = 6;
	float magnitude = .1;

	void script() override{
		glm::vec3 nsway = axis * magnitude * cosf(engine::timer.t * transform::pi * 2 / period);
		glm::vec3 dsway = nsway - sway;
		sway = nsway;

		engine::cam.tform.loc += dsway;

		//deprecated
		//float density = .3;
		//float fogcolor[4] = { .1, .5, .9, 1 };
		//glEnable(GL_FOG);
		//glFogi(GL_FOG_MODE, GL_EXP2);
		//glFogfv(GL_FOG_COLOR, fogcolor);
		//glFogf(GL_FOG_DENSITY, density);
	}
	
	//could render post-process, add blue scaled by depth buffer vals
};

void wrecksite()
{
	printf("\nWrecksite will contain two distant large planets, a sun a moon. A wreck with coral growing on it.\n");
	printf("\nPress enter to continue\n");
	std::cin.get();

	engine::cam.setdebug(true);

	wreck = new object;
	engine::scene.spawn(wreck);

	wreck->mod = model({ "engine/models/box.dat" });

	object* planet = engine::scene.spawn(new object);
	planet->mtl.adsa = { 0, 1, 0, 32 };
	planet->mtl.rgba = { .25, .75, .75, 1 };
	planet->tform.scale *= 100;
	planet->tform.loc.x = -500;

	planet = engine::scene.spawn(new object);
	planet->mtl.adsa = { 0, 1, 0, 32 };
	planet->mtl.rgba = { .8, .2, .1, 1 };
	planet->tform.scale *= 400;
	planet->tform.loc.z = -500;

	planet = engine::scene.spawn(new object);
	planet->mtl.adsa = { 1, 0, 0, 32 };
	planet->mtl.rgba = { 1, 1, .8, 1 };
	planet->tform.scale *= 50;
	planet->tform.loc = { 500,500,500 };

	planet = engine::scene.spawn(new object);
	planet->mtl.adsa = { 0, 1, 0, 32 };
	planet->mtl.rgba = { .5, .5, .1, 1 };
	planet->tform.scale *= 10;
	planet->tform.loc = { 0,100,-100 };

	object *test = engine::scene.spawn(new object);
	test->tform.scale = { 1000,1000,1 };
	test->tform.loc.z = 100;
	test->mod = model({ "engine/models/box.dat" });

	engine::scene.spawn(new ether);

}