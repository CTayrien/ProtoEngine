/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include <ctime>

#include "engine\engine.h"

#include "asteroid.h"
#include "enemycraft.h"
#include "playarea.h"
#include "playerbullet.h"
#include "playercraft.h"

int main()
{
	srand(time(0));

	engine::scene.add(new playercraft);
	
	// prefab asteroids spawn (brown sphere)
	//		if collides with player, destroy it and this
	//		if collides with active bullet, destroy it and this
	//		if doesn't collide with play area, destroy it

	// prefab enemies spawn (red tet)
	//		if collides with player, destroy it and this
	//		if collides with active bullet, destroy it and this
	//		if doesn't collide with play area, destroy it

	
	// when player clicks, prefab bullet spawns (white box)

	//		if player doesn't collide with play area, lerp location to clamped play area

	// player avoids asteroids and enemies

	// player hits asteroids and enemies with bullets 
	//	(asteroids and enemies have reference to 10 bullets, which may be active)
	
	engine::cam.tform.loc.z = 50;
	engine::cam.setdebug(false);

	engine::start();

	return 0;
}