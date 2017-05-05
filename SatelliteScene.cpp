/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "engine\engine.h"
#include "objects\globe\Globe.h"

int main()
{
	Globe globe;
	
	engine::scene.add(&globe);
	
	engine::start();

	return 0;
}