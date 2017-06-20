/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "transform.h"
#include "engine.h"

#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\quaternion.hpp>

float transform::pi = glm::pi<float>();

transform::transform()
{
}

transform::~transform()
{
}

glm::vec3 transform::forward()
{
	return -R[2];
}

glm::vec3 transform::up()
{
	return R[1];
}

glm::vec3 transform::right()
{
	return R[0];
}

glm::vec3 transform::lookat()
{
	return loc + forward();
}

//void transform::setroll(float roll)
//{
//	rot.z = roll;
//	setyawpitchroll(rot);
//}

void transform::setyawpitchroll(glm::vec3 rot)
{
	R = taitbryant(rot);
}

//void transform::setforward(glm::vec3 f)
//{
//	float pitch = -asinf(f.y);
//	float yaw = atan2(f.x, f.z);
//
//	setyawpitchroll(glm::vec3(pitch, yaw, 0));
//}

void transform::setforwardandroll(glm::vec3 f, float roll)
{
	float pitch = -asinf(f.y);
	float yaw = atan2(f.x, f.z);

	setyawpitchroll(glm::vec3(pitch, yaw, roll));
}

glm::vec3 projvecplane(glm::vec3 a, glm::vec3 b) {
	return a - b * glm::dot(a, b);
}

//void transform::setright(glm::vec3 r)
//{
//	// This does not work
//	// Project y vector onto plane perpendicular to right vector
//	glm::vec3 up = glm::normalize(projvecplane({ 0,1,0 }, r));
//
//	glm::vec3 forward = glm::cross(up, r);
//
//	R = {	r.x, r.y, r.z,
//			up.x, up.y, up.z,
//			forward.x, forward.y, forward.z };
//}

//the drot in cam is measured in cam frame
//the drot in rollaball is in world frame
// concatenates rotations 
// should overload a version that takes axis-angle
// should have a version that slerps (slerp is not most direct path, however - overload again)
// What is the dif between R = R * D and R = D * R? dogfight camera needs first, rollaball needs 2nd. rollaball should try 1st with -1 times the delta it currently uses
void transform::drotin(glm::vec3 dyawpitrol)
{
	R = R * taitbryant(dyawpitrol);
}

// does not concatenate rotations
// To Do: Does not account for roll. Yaw & Pitch (pitch clamped to +/- 90 deg) could use alternate func "accumulate" that works intrinsicly for dogfight
void transform::drotex(glm::vec3 dyawpitrol)
{
	glm::vec3 ypr = glm::vec3(asinf(forward().y), atan2f(-right().z, right().x), 0);
	ypr += dyawpitrol;
	ypr.x = glm::clamp(ypr.x, -pi / 2, pi / 2);
	setyawpitchroll(ypr);
}

glm::mat3 transform::slerp(const glm::mat3& a, const glm::mat3& b, float t)
{
	return glm::toMat3(glm::slerp(glm::quat(a), glm::quat(b), t));
}

glm::mat3 transform::rodrigz(glm::vec3 axis, float angle)
{
	if (axis == glm::vec3()) return glm::mat3();
	return glm::mat3(glm::rotate(angle, axis));
}

glm::vec3 transform::norm(glm::vec3 v)
{
	if (v == glm::vec3()) return glm::vec3();
	return glm::normalize(v);
}

glm::mat3 transform::taitbryant(glm::vec3 pityawrol)
{
	return glm::mat3(glm::yawPitchRoll(pityawrol.y, pityawrol.x, pityawrol.z));
}

void transform::physicsupdate()
{
	vel += force / mass * engine::timer.dt;
	loc += vel * engine::timer.dt;
	force = { 0, 0, 0 };

	//rotvel += torque / moment * engine::timer.dt;
	//rot += rotvel * engine::timer.dt;
	//torque = { 0, 0, 0 };
	//setyawpitchroll(rot);
}