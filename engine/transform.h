/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include <glm\glm.hpp>

class transform
{
public:
	// Can/should I use quaternion instead of rot (yaw pitch roll) and R?
	glm::vec3 loc, scale = {1,1,1};
	
	glm::mat3 R;	// need for collision detection, camera matrix, etc.
	//glm::quat q;	// could use for slerp and derive ypr and R from this?

	glm::vec3 vel, force;
	float mass = 1;

	glm::vec3 rotvel, torque;
	float moment = 1;	//should be derived per-axis? is there an inertia tensor?

	transform();
	~transform();

	glm::vec3 forward();
	glm::vec3 up();
	glm::vec3 right();
	glm::vec3 lookat();

	void setyawpitchroll(glm::vec3 rot);
	void setforwardandroll(glm::vec3 f, float roll);
	//void setroll(float roll);
	//void setforward(glm::vec3 f);
	
	void drotin(glm::vec3 dyawpitrol);
	void drotex(glm::vec3 dyawpitrol);

	static glm::mat3 slerp(const transform& a, const transform& b, float t);

	void physicsupdate();
};