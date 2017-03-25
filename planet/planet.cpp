/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

// Create the behavior of a new type of game object in a game or scene
#include "planet.h"

#include <iostream>

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
void planet::update()
{
	tform.update();

	if (collides<SPHERE>(engine::cam)) {
		system("cls");
		printf("Collision.\n");
	}
}