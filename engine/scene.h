/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"

class scene
{
public:
	int nobjs;

	object* objects[1024];

	object * spawn(object* object);
	
	void clean();

	object* back();

	scene();
	~scene();
};