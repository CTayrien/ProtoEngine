/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

// Create the behavior of a new type of game object in a game or scene
#include "planet.h"

#include <iostream>

void planet::push(object * obj)
{
	objs.push_back(obj);
}

// c'tor
planet::planet(model * mod, texture * tex)
{
	tag = "myobjtag";
	this->mod = mod;
	this->tex = tex;

	tform.scale = { .1, .1, .1 };
	tform.rotvel = { 0, .1, 0 };
}

// d'tor
planet::~planet()
{
}

// update
void planet::script()
{
	//tform.derivematrix();

	if (collides<SPHERE,SPHERE>(engine::camera)) {
		system("cls");
		printf("Collision.\n");
	}

	for(object* obj : objs){
		glm::vec3 r = obj->tform.loc - tform.loc;
		glm::vec3 dir = glm::normalize(r);
		float rsqrd = glm::dot(r, r);
		
		// f = g mm/rr
		obj->tform.force -= dir * G / rsqrd * (obj->tform.mass * tform.mass);

		// f = vm/r	-> v = f / m * r
		float vmag = glm::length(obj->tform.force) / obj->tform.mass * (glm::length(r));
		glm::vec3 vdir = glm::cross(glm::vec3(0, 1, 0), dir);

		obj->tform.vel = vdir * vmag;
	}
}