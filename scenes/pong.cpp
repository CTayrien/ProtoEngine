/* Pong: free open-source prototype pong game
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "pong.h"
#include "engine.h"
#include <iostream>

object* pongball;
object* pongplayer1;
object* pongplayer2;
object* pongfloor;
object* pongceiling;

class paddle :public object {
public:
	int upkey;
	int downkey;
	bool iscolliding;
	glm::vec3 forward;

	paddle(int upkey, int downkey, glm::vec3 forward) {
		tag = "Paddle";
		mod = model({ "engine/models/box.dat" });
		tex = texture({ "engine/textures/white.png" });
		tform.scale = { .1f , 2.0f, 2.0f};
		this->upkey = upkey;
		this->downkey = downkey;
		this->forward = forward;
	}

	void script() override
	{
		if (engine::input.down[input_z]) {
			pongball->tform.loc = {};
			pongball->tform.vel.y = 0;
		}

		if (collides<BOX, SPHERE>(*pongball)) {
			if (!iscolliding) {
				iscolliding = true;

				float c = glm::dot(pongball->tform.vel, forward);
				pongball->tform.vel -= 2.f * c * forward;

				pongball->tform.vel += tform.vel / 2.f;
			}
		}
		else {
			iscolliding = false;
		}

		if (engine::input.down[upkey]) {
			tform.vel.y = 5;
		}
		else if (engine::input.down[downkey]) {
			tform.vel.y = -5;
		}
		else {
			tform.vel.y = 0;
		}
	}
};

void pong()
{
	printf("Welcome to Proto Engine's pong.\nW/S to move left player, Up/Dn to move right player\nZ resets ball\n\nPress Enter to begin\n");
	std::cin.get();

	pongball = engine::scene.spawn(new object);
	pongball->tform.vel.x = 10;
	pongball->mtl.rgba = { .2,.2,.2,1 };
	
	pongplayer1 = engine::scene.spawn(new paddle(input_up, input_down, {1,0,0}));
	pongplayer1->tform.loc.x = 10;
	pongplayer1->mtl.rgba = { 1,.5,.5,1 };
	pongplayer1->mtl.adsa = { 1,0,0,32 };

	pongplayer2 = engine::scene.spawn(new paddle(input_w, input_s, { 1,0,0 }));
	pongplayer2->tform.loc.x = -10;
	pongplayer2->mtl.rgba = { .5,1,.5,1 };
	pongplayer2->mtl.adsa = { 1,0,0,32 };

	pongceiling = engine::scene.spawn(new paddle(0, 0, { 0,-1,0 }));
	pongceiling->tform.loc.y = 8;
	pongceiling->tform.scale = { 20, .1, 5 };

	pongfloor = engine::scene.spawn(new paddle(0, 0, { 0,1,0 }));
	pongfloor->tform.loc.y = -8;
	pongfloor->tform.scale = { 20, .1, 5 };

	object* back = engine::scene.spawn(new object);
	back->mod = model({ "engine/models/box.dat" });
	back->tform.loc.z = -5;
	back->tform.scale *= 20;
	back->tform.scale.z = 1;
	back->mtl.rgba = { .5,.5,1,1 };
	back->mtl.adsa = { 1,0,0,32 };
}