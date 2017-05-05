/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "transform.h"
#include "engine.h"

#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\quaternion.hpp>

transform::transform()
{
	scale = { 1, 1, 1 };
	
	loc = vel = force = { 0, 0, 0 };
	mass = 1;

	rot = rotvel = torque = { 0, 0, 0 };
	moment = 1;
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

void transform::setroll(float roll)
{
	rot.z = roll;
	derivematrix();
}

void transform::setforward(glm::vec3 f)
{
	float pitch = -asinf(f.y);
	float yaw = atan2(f.x, f.z);

	rot = glm::vec3{ pitch, yaw, rot.z };
	
	derivematrix();
}

void transform::physicsupdate()
{
	vel += force / mass * engine::timer.dt;
	loc += vel * engine::timer.dt;
	force = { 0, 0, 0 };

	rotvel += torque / moment * engine::timer.dt;
	rot += rotvel * engine::timer.dt;
	torque = { 0, 0, 0 };

	derivematrix();
}

void transform::derivematrix()
{
	R = (glm::mat3)glm::yawPitchRoll(rot.y, rot.x, rot.z);
}
