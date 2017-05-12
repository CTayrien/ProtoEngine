/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "lerparrow.h"
#include <engine.h>
#include <glm/gtx/quaternion.hpp>

lerparrow::lerparrow()
{
	delete tex;
	tex = new texture({ "engine/textures/red.png" });
}

lerparrow::~lerparrow()
{
}

void lerparrow::script()
{
	// Try to stop
	if ((d > 0.0f && t >= 1.0f) ||
		(d < 0.0f && t <= 0.0f)) {
		d *= -1.0f;
		go = false;
	}
	
	// Try to start
	if (engine::input.down[input_enter]) {
		go = true;
	}
	
	// Increase or decrease t from 0 to 1 and back
	if (go) {
		t += d * f * engine::timer.dt;
	}

	// Lerp
	tform.rot = glm::mix(a->rot, b->rot, t);

	// Derive delta r-axis or global r-axis from delta rot or tform.rot ?
	// cross current <0,0,-1> with previous <0,0,-1> ?

	//tform.derivematrix();
}