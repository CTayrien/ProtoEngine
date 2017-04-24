/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "slerparrow.h"
#include <engine.h>
#include <glm/gtx/quaternion.hpp>

slerparrow::slerparrow()
{
	delete tex;
	tex = new texture("engine/textures/green.png");
}

slerparrow::~slerparrow()
{
}

void slerparrow::update()
{
	// Try to stop
	if ((d > 0.0f && t >= 1.0f) ||
		(d < 0.0f && t <= 0.0f)) {
		d *= -1.0f;
		if (d > 0) t = 0;
		else t = 1;
		go = false;
	}

	// Try to start
	if (input::isDown(input_enter)) {
		go = true;
	}

	// Increase or decrease t from 0 to 1 and back
	if (go) {
		t += d * f * engine::time.dt;
	}

	// Slerp
	//#include <glm\gtx\quaternion.hpp>
	glm::quat qa(a->rotmat);
	glm::quat qb(b->rotmat);

	glm::quat qt = glm::slerp(qa, qb, t);

	tform.rotmat = glm::toMat4(qt);
	
	// derive yaw,pitch,roll from qt or rotmat & update tform...or just do this
	tform.modelWorld =
		glm::translate(tform.loc) *
		tform.rotmat *
		glm::scale(tform.scale);

	// render an axis in direction d = normalize(v)
	// scale is s = length(v)
}