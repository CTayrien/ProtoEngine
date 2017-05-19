/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "model.h"
#include "texture.h"
#include "transform.h"

enum collider { SPHERE, BOX };

class object
{
public:
	std::string tag = "default tag";
	bool garbage = false;
	model mod;
	texture tex;
	transform tform;
	
	glm::vec3 e;
	float r;

	object();
	virtual ~object();
	
	virtual bool loaded();
	virtual bool load();
	
	void update();
	virtual void script();
	virtual void render();

	template<collider, collider>
	bool collides(const object& b) const;
};