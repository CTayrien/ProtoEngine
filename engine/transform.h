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

	// Do I really need to store all of these?
	glm::mat3 R;
	glm::mat3 normtform;
	glm::mat4 rotmat;
	glm::mat4 scalemat;
	glm::mat4 transmat;
	glm::mat4 modelWorld;

	glm::vec3 vel, force;
	float mass;

	glm::vec3 rotvel, torque;
	float moment;

	transform();
	~transform();

	glm::vec3 forward();
	glm::vec3 up();
	// right();
	// lookat();

	void setroll(float roll);
	// void set yaw, pitch?

	void setforward(glm::vec3 f);

	void physicsupdate();

	void derivematrix();
};