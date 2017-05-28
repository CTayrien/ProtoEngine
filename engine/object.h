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

struct material {
	// ambient, diffuse, specular, alpha
	glm::vec4 adsa = { .5, .5, .5, 32 };
	glm::vec4 rgba = { 1, 1, 1, 1 };
};

class object
{
public:
	std::string tag = "default tag";
	bool garbage = false;
	transform tform;
	model mod;
	texture tex;
	//glm::vec4 mtl[2] = {{ .5, .5, .5, 32 },	//ambient, diffuse, specular, alpha
	//					 { 1, 1, 1, 1 }};	//rgba
	material mtl;

	glm::vec3 e;
	float r;

	object();
	object(std::string tag, model mod, texture tex);
	virtual ~object();
	
	virtual bool loaded();
	virtual bool load();
	
	void update();
	virtual void script();
	virtual void render();

	template<collider, collider>
	bool collides(const object& b) const;
};