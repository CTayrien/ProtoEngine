/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include <glm\glm.hpp>

class transform
{
public:
	glm::vec3 loc, rot, scale;
	glm::mat3 R;
	glm::mat4 modelWorld;

	glm::vec3 vel, force;
	float mass;

	glm::vec3 rotvel, torque;
	float moment;

	transform();
	~transform();

	void update();
	void render();
};