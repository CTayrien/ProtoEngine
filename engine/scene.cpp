/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "scene.h"
#include "engine.h"

object * scene::spawn(object * object)
{
	if (nobjs < 1024) {
		objects[nobjs++] = object;
		
		// if engine started, load object
		if (engine::window.ptr)
			object->load();
	}
	else {
		printf("Scene full - object spawn failed.");
	}

	return object;
}

// currently causes crashes sometimes (deleting random 10 out of 100 on first frame?)
void scene::clean()
{
	// Number removed
	int n = 0;

	for (int i = 0; i < nobjs; i++) {
		if (objects[i]->garbage) {
			delete objects[i];
			n++;
		}

		if (n > 0) {
			if (i < nobjs - n)
				objects[i] = objects[i + n];
			else
				objects[i] = nullptr;
		}
	}
	nobjs -= n;
}

object * scene::back()
{
	return objects[nobjs - 1];
}

scene::scene()
{
	nobjs = 2;
	objects[0] = new skybox;
	objects[1] = new camera;
}

scene::~scene()
{
}