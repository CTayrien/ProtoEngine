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

void slerparrow::script()
{
	// Try to stop/start t increasing to 1 or decreasing to 0 over 3 seconds
	if ((d > 0.0f && t >= 1.0f) ||
		(d < 0.0f && t <= 0.0f)) {
		d *= -1.0f;
		go = false;
	}
	if (input::isDown(input_enter)) {
		go = true;
	}
	if (go) {
		t += d * f * engine::time.dt;
	}
	// Slerp with t
	//#include <glm\gtx\quaternion.hpp>
	glm::quat qa(a->rotmat);
	glm::quat qb(b->rotmat);
	glm::quat qt = glm::slerp(qa, qb, t);
	
	// Set orientation of slerp object "spacecraft"
	//tform.setforward((glm::vec3)glm::rotate(qt, glm::vec4(0, 0, -1, 1)));
	//tform.setroll(?);
	//tform.updatematrix();//upside-down?
	
	tform.rotmat = glm::toMat4(qt);

	tform.modelWorld =
		glm::translate(tform.loc) *
		tform.rotmat *
		glm::scale(tform.scale);		//dont updatematrix because it never got .rot set



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
	qavector->setforward(-glm::normalize(qva));
	qavector->setroll(-engine::pi * glm::length(qva));
	qavector->derivematrix();

	//qb
	glm::vec3 qvb = glm::vec3{ qb.x, qb.y, qb.z };
	qbvector->loc = qvb;
	qbvector->setforward(-glm::normalize(qvb));
	qbvector->setroll(-engine::pi * glm::length(qvb));
	qbvector->derivematrix();

	// Set location/orientation of quaternion Vector object (screw / bolt)
	glm::vec3 qv = glm::vec3{ qt.x, qt.y, qt.z };
	glm::vec3 dv = qv - qtvector->loc;
	qtvector->loc = qv;
	qtvector->setforward(-glm::normalize(qv));
	qtvector->setroll(-engine::pi * glm::length(qv));
	qtvector->derivematrix();
	
	// Move orientation b "Beijing"
	float c = 180.f / engine::pi;
	float s = 60.0f / engine::time.fps / c;
	if (input::isDown(input_right)) {
		b->rot.x += 1.f * s;
		printf("Yaw: %f\n", b->rot.y * c);
	}
	if (input::isDown(input_left)) {
		b->rot.x -= 1.f * s;
		printf("Yaw: %f\n", b->rot.y * c);
	}
	if (input::isDown(input_up)) {
		b->rot.y += 1.f * s;
		printf("Roll: %f\n", b->rot.x * c);
	}
	if (input::isDown(input_down)) {
		b->rot.y -= 1.f * s;
		printf("Roll: %f\n", b->rot.x * c);
	}
	if (input::isDown(GLFW_KEY_EQUAL)) {
		b->rot.z += 1.f * s;
		printf("Roll: %f\n", b->rot.z * c);
	}
	if (input::isDown(GLFW_KEY_MINUS)) {
		b->rot.z -= 1.f * s;
		printf("Roll: %f\n", b->rot.z * c);
	}
	b->derivematrix();

	// Set location/orientation of camera
	if (input::isDown(input_ctrl_left))
		engine::cam.tform.loc += dv;
}