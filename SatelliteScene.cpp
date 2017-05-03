/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "engine\engine.h"
#include "globe\Globe.h"

int main() 
{
	//scene is composed of objects
	Globe globe;
	globe.mod->filename = "engine/models/sphere2.dat";
	
	// play game should be built in
	if(!engine::start()) return -1;

	globe.load();
	engine::cam.setisfps(false);

	while (!engine::inputdown(input_esc)) 
	{	
		engine::update();

		if (engine::inputdown(input_1))
			engine::cam.setisfps(true);
		if (engine::inputdown(input_2))
			engine::cam.setisfps(false);

		// these calls should be built in
		globe.update();

		globe.render();

	}

	engine::stop();

	return 0;
}