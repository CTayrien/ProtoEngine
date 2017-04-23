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

void transform::update()
{
	vel += force / mass * engine::time.dt;
	loc += vel * engine::time.dt;
	force = {0, 0, 0};

	rotvel += torque / moment * engine::time.dt;
	rot += rotvel * engine::time.dt;
	torque = {0, 0, 0};

	rotmat = glm::yawPitchRoll(rot.y, rot.x, rot.z);
	
	R = (glm::mat3)rotmat;

	modelWorld = glm::translate(loc) * rotmat	* glm::scale(scale);
}

void transform::render()
{
	glUniformMatrix4fv(3, 1, GL_FALSE, &modelWorld[0][0]);
}