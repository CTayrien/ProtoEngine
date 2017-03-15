/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "transform.h"
#include "engine.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

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

void transform::update()
{
	vel += force / mass * engine::time.dt;
	loc += vel * engine::time.dt;
	force = {0, 0, 0};

	rotvel += torque / moment * engine::time.dt;
	rot += rotvel * engine::time.dt;
	torque = { 0, 0, 0 };

	glm::mat4 rotation = glm::yawPitchRoll(rot.y, rot.x, rot.z);
	R = (glm::mat3)rotation;
	modelWorld = glm::translate(loc)
		* rotation
		* glm::scale(scale);
}

void transform::render()
{
	glm::mat4 tform = glm::translate(loc)
		* glm::yawPitchRoll(rot.y, rot.x, rot.z)
		* glm::scale(scale);

	glUniformMatrix4fv(3, 1, GL_FALSE, &tform[0][0]);
}