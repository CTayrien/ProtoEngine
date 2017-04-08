/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

// Create the behavior of a new type of game object in a game or scene

#pragma once

#include <vector>

// 1) Include engine header
#include "engine.h"

// 2) Inherit obj publicly
class planet :
	public object
{
	struct orbit {
		float semimajoraxis;
		float semiminoraxis;
		glm::vec3 a, b;
		float orbitalperiod;
		glm::vec3 curloc, curvel;
		float phase;
		object* barycenter;
		float eccentricity;
	};

private:
	float G = .1f;
	std::vector<object*> objs;
public:
	void push(object* objs);
	// 3) Create a constructor that initializes the obj member data "string tag" and "model"
	planet(model* mod, texture* tex);

	// 4) Override the destructor. If c'tor allocates memory, d'tor deallocates it.
	~planet() override;

	// 5) Override the update method with game logic. May access members of physics:: and input:: and call rigidbody.update
	void update() override;
};