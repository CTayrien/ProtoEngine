/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include <glm\glm.hpp>

class transform
{
public:
	// Can/should I use quaternion instead of yaw pitch roll?
	glm::vec3 loc, rot, scale;
	glm::mat3 R;

	glm::vec3 vel, force;
	float mass;

	glm::vec3 rotvel, torque;
	float moment;

	transform();
	~transform();

	glm::vec3 forward();
	glm::vec3 up();
	glm::vec3 right();
	glm::vec3 lookat();

	void setroll(float roll);
	// void set yaw, pitch?

	void setforward(glm::vec3 f);

	void physicsupdate();
	void derivematrix();
};