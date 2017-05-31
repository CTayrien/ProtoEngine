/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "slerparrow.h"
#include <engine.h>
#include <glm/gtx/quaternion.hpp>

slerparrow::slerparrow()
{
	tex = texture({ "engine/textures/green.png" });
}

slerparrow::~slerparrow()
{
}

void slerparrow::script()
{
	// Try to stop/start t increasing to 1 or decreasing to 0 over 3 seconds
	if ((d > 0.0f && t >= 1.0f) ||
		(d < 0.0f && t <= 0.0f)) {
		d *= -1.0f;
		go = false;
	}
	if (engine::input.down[input_enter]) {
		go = true;
	}
	if (go) {
		t += d * f * engine::timer.dt;
	}
	// Slerp with t
	//#include <glm\gtx\quaternion.hpp>
	glm::quat qa(a->R);
	glm::quat qb(b->R);
	glm::quat qt = glm::slerp(qa, qb, t);

	tform.R = glm::toMat3(qt);

	// derp draws back one quaternion, then adds the other.
	//float t2 = glm::abs(2 * t - (int)(2 * t));
	//if (t >= 1.0f) t2 = 1.0f;
	//glm::quat q0;
	//glm::quat qx = (t<.5) ? (qa) : (q0);
	//glm::quat qy = (t<.5) ? (q0) : (qb);
	//glm::quat qd = glm::slerp(qx, qy, t2);
	//
	//derper->rotmat = glm::toMat4(qd);
	//derper->modelWorld =
	//	glm::translate(derper->loc) *
	//	derper->rotmat *
	//	glm::scale(derper->scale);
	//
	//glm::vec3 qvd = glm::vec3{ qd.x, qd.y, qd.z };
	//qdvector->loc = qvd;
	//qdvector->setforward(-glm::normalize(qvd));
	//qdvector->setroll(-engine::pi * glm::length(qvd));
	//qdvector->updatematrix();

	//qa
	glm::vec3 qva = glm::vec3{ qa.x, qa.y, qa.z };
	qavector->loc = qva;
	qavector->setforwardandroll(-glm::normalize(qva), -transform::pi * glm::length(qva));

	//qb
	glm::vec3 qvb = glm::vec3{ qb.x, qb.y, qb.z };
	qbvector->loc = qvb;
	qbvector->setforwardandroll(-glm::normalize(qvb), -transform::pi * glm::length(qvb));

	// Set location/orientation of quaternion Vector object (screw / bolt)
	glm::vec3 qv = glm::vec3{ qt.x, qt.y, qt.z };
	glm::vec3 dv = qv - qtvector->loc;
	qtvector->loc = qv;
	qtvector->setforwardandroll(-glm::normalize(qv), -transform::pi * glm::length(qv));
	
	// Move orientation b "Beijing"
	//float c = 180.f / engine::pi;
	//float s = 60.0f * engine::timer.dt / c;
	//if (engine::isdown(input_right)) {
	//	b->rot.x += 1.f * s;
	//	printf("Yaw: %f\n", b->rot.y * c);
	//}
	//if (engine::isdown(input_left)) {
	//	b->rot.x -= 1.f * s;
	//	printf("Yaw: %f\n", b->rot.y * c);
	//}
	//if (engine::isdown(input_up)) {
	//	b->rot.y += 1.f * s;
	//	printf("Roll: %f\n", b->rot.x * c);
	//}
	//if (engine::isdown(input_down)) {
	//	b->rot.y -= 1.f * s;
	//	printf("Roll: %f\n", b->rot.x * c);
	//}
	//if (engine::isdown(GLFW_KEY_EQUAL)) {
	//	b->rot.z += 1.f * s;
	//	printf("Roll: %f\n", b->rot.z * c);
	//}
	//if (engine::isdown(GLFW_KEY_MINUS)) {
	//	b->rot.z -= 1.f * s;
	//	printf("Roll: %f\n", b->rot.z * c);
	//}
	//b->derivematrix();

	// Set location/orientation of camera
	if (engine::input.down[input_ctrl])
		engine::cam.tform.loc += dv;
}