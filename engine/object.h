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
	model* mod = nullptr;
	texture* tex = nullptr;
	transform tform;

	object();
	virtual ~object();
	
	void load();
	void unload();
	
	void update();
	virtual void script() = 0;
	virtual void render();

	template<collider, collider>
	bool collides(const object& b) const;
};