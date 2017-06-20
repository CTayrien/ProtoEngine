/* Wrecksite: free open-source prototype sci-fi exploration game in ethereal space.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "wrecksite.h"
#include "engine.h"

#include <iostream>

#include "shoal/shoal.h"
#include "shark/shark.h"

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
	}
	
	void render() override {
		//fog is currently in shader, should post-process in overloaded render, add blue scaled by depth buffer vals
	}
};

void wrecksite()
{
	printf("\nWrecksite will contain two distant large planets, a sun a moon. A wreck with coral growing on it.\n");
	printf("\nPress enter to continue\n");
	std::cin.get();

	engine::cam.setdebug(true);

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
	planet->tform.loc = { 500, 500, 500 };

	planet = engine::scene.spawn(new object);
	planet->mtl.adsa = { 0, 1, 0, 32 };
	planet->mtl.rgba = { .5, .5, .1, 1 };
	planet->tform.scale *= 10;
	planet->tform.loc = { 0, 100, -100 };

	engine::scene.spawn(new ether);

	// shoal and shark
	shark* theshark = (shark*) engine::scene.spawn(new shark);
	theshark->tform.loc = { 10, -10, 10 };

	shoal* theshoal = (shoal*) engine::scene.spawn(new shoal);
	theshoal->theshark = theshark;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				theshoal->fishes.push_back((fish*)engine::scene.spawn(new fish));
				theshoal->fishes.back()->theshoal = theshoal;
				theshoal->fishes.back()->tform.loc = {(i - 5)*5 , (j - 5) * 5 , (k - 5) * 5 };
			}
		}
	}
}