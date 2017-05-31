/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"

class scene
{
public:
	// Up to 1024 objects per scene (includes cam & sky)
	object* objects[1024];
	int nobjs = 0;

	// object* obj = spawn(new object); (scene will delete it if garbage or when game over)
	object* spawn(object* object);
	
	// Removes objects with .garbage == true (crashes on scene with 1000 objects when many are deleted in first frame)
	void clean();
	void prime();
	void empty();

	object* back();

	scene();
	~scene();
};