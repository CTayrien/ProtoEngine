/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

// Create the behavior of a new type of game object in a game or scene
#include "objecta.h"

#include <iostream>

// c'tor
objecta::objecta(model * mod, texture * tex)
{
	tag = "myobjtag";
	this->mod = mod;
	this->tex = tex;

	tform.scale = { .1, .1, .1 };
	tform.rotvel = { 0, .1, 0 };
}

// d'tor
objecta::~objecta()
{
}

// update
void objecta::update()
{
	tform.update();

	if (collides<SPHERE>(engine::cam)) {
		system("cls");
		printf("Collision.\n");
	}
	//ticker += engine::time.dt;
	//if (ticker > .01) {
	//	ticker = 0;
		//system("cls");
		//std::cout << "Updating. (Framerate = " << engine::time.t << ")\n";
	//}
}