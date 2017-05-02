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
	engine::start();

	globe.load();

	while (!input::isDown(input_esc)) 
	{	
		engine::update();

		// these calls should be built in
		globe.update();

		globe.render();

	}

	engine::stop();

	return 0;
}