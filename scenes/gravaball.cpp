/* Grav-a-Ball: free open-source prototype gravity simulation with 1000 falling cubes.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "gravaball.h"

#include <ctime>
#include "engine.h"
#include "objects/rollaball/rollaball.h"
#include "objects/collectible/collectible.h"
#include "objects/satellite/satellite.h"

void spawnitems(rollaball* player, object* satellite[4], int n)
{
	srand(time(0));

	for (int i = 0; i < n; i++) {
		collectible& c = *(collectible*)engine::scene.spawn(new collectible);
		c.player = player;
		c.satellite[0] = satellite[0];
		c.satellite[1] = satellite[1];
		c.satellite[2] = satellite[2];
		c.satellite[3] = satellite[3];

		c.tform.loc.x = (float)rand() / (float)RAND_MAX * 20 - 10;
		c.tform.loc.y = (float)rand() / (float)RAND_MAX * 20 - 10;
	}
}

void gravaball() {
	// Player
	rollaball& player = *(rollaball*)engine::scene.spawn(new rollaball);;

	// Satellites
	object* sats[4];
	sats[0] = engine::scene.spawn(new satellite(&player, 0.f));
	sats[1] = engine::scene.spawn(new satellite(&player, .25f));
	sats[2] = engine::scene.spawn(new satellite(&player, .50f));
	sats[3] = engine::scene.spawn(new satellite(&player, .75f));

	// Collectibles
	spawnitems(&player, sats, 1000);

	engine::cam.tform.loc.z = 16;
	engine::cam.setdebug(false);
}