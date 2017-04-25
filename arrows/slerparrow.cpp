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
	bool nothingmoved = true;

	// Try to stop/start t increasing to 1 or decreasing to 0 over 3 seconds
	if ((d > 0.0f && t >= 1.0f) ||
		(d < 0.0f && t <= 0.0f)) {
		d *= -1.0f;
		go = false;
	}
	if (input::isDown(input_enter)) go = true;
	if (go) {
		t += d * f * engine::time.dt;
		nothingmoved = false;
	}
	// Slerp with t
	//#include <glm\gtx\quaternion.hpp>
	glm::quat qa(a->rotmat);
	glm::quat qb(b->rotmat);
	glm::quat qt = glm::slerp(qa, qb, t);
	
	// Set orientation of slerp object "spacecraft"
	tform.rotmat = glm::toMat4(qt);
	tform.modelWorld =
		glm::translate(tform.loc) *
		tform.rotmat *
		glm::scale(tform.scale);		//dont updatematrix because it never got .rot set

	// Set location/orientation of quaternion Vector object (screw / bolt)
	glm::vec3 qv = glm::vec3{ qt.x, qt.y, qt.z };
	glm::vec3 dv = qv - qtvector->loc;
	qtvector->loc = qv;
	qtvector->setforward(-glm::normalize(qv));
	qtvector->setroll(-engine::pi * glm::length(qv));
	qtvector->updatematrix();
	
	// Move orientation b "Beijing"
	float c = 180.f / engine::pi;
	float s = 60.0f / engine::time.fps / c;
	if (input::isDown(input_right)) {
		b->rot.y += 1.f * s;
		printf("Yaw: %f\n", b->rot.y * c);
		nothingmoved = false;
	}
	if (input::isDown(input_left)) {
		b->rot.y -= 1.f * s;
		printf("Yaw: %f\n", b->rot.y * c);
		nothingmoved = false;
	}
	if (input::isDown(input_up)) {
		b->rot.x += 1.f * s;
		printf("Roll: %f\n", b->rot.x * c);
		nothingmoved = false;
	}
	if (input::isDown(input_down)) {
		b->rot.x -= 1.f * s;
		printf("Roll: %f\n", b->rot.x * c);
		nothingmoved = false;
	}
	if (input::isDown(GLFW_KEY_EQUAL)) {
		b->rot.z += 1.f * s;
		printf("Roll: %f\n", b->rot.z * c);
		nothingmoved = false;
	}
	if (input::isDown(GLFW_KEY_MINUS)) {
		b->rot.z -= 1.f * s;
		printf("Roll: %f\n", b->rot.z * c);
		nothingmoved = false;
	}
	b->updatematrix();

	//if (nothingmoved) return;
	// Set location/orientation of camera
	//glm::vec3 loc = qv*1.1f;
	//float t = .001;
	//engine::cam.tform.loc = glm::mix(engine::cam.tform.loc, loc, t);
	if (input::isDown(input_ctrl_left))
		engine::cam.tform.loc += dv;
}