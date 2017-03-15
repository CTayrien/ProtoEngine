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

// want collider.h - include it here
enum collider { AABB, SPHERE, OBB };	// def this in collider.h, call it colliderenum

class object
{
public:
	std::string tag = "default tag";
	model* mod = nullptr;
	texture* tex = nullptr;
	transform tform;
	// have a collider class here. data: s, r, r2. vals get set in collider.init, after model loads (data the model saves is not needed ever again)
	
	object();
	virtual ~object();
	virtual void update() = 0;
	void render();

	// Cache these on collider class after model loading, or any time scale or model changes
	// Collisions
	glm::vec3 s() const;
	float r() const;		// currently calc incorrect - max(s). should be mag(s)
	float r2() const;

	template<collider type>	// declared here, but specialized dec & def in collision.h & cpp
	bool collides(const object& b) const;
};

// spec defs go ... in collision.h? no, here... defined in cpp? no... nowhere?
//template<>
//bool object::collides<AABB>(const object& b) const;
//
//template<>
//bool object::collides<SPHERE>(const object& b) const;
//
//template<>
//bool object::collides<OBB>(const object& b) const;