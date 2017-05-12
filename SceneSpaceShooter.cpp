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

void spawnasteroids(const asteroid& prefab, asteroid* asteroids, int nasteroids) {

}

void spawnenemies(const enemycraft& prefab, enemycraft* enemies, int nenemies) {

}

int main()
{
	// scene should store new'd pointers via spawn function
	// they are erase-removed and deleted by the despawn func. when game exits, all are despawned, then resource maps are unloaded
	
	// all objects have their own assets. these get their integer vals from the map. the map stores ptrs. the derived class provide a way to new and delete texs from the single polymorphic map? yes - texture.load would have a new if necessary, and texture.unload would delete things. could keep ref counter and/or use smart pointer, and auto-unload when despawning

	srand(time(0));

	model models[4] = {
		std::vector<std::string>{"engine/models/sphere.dat"},
		std::vector<std::string>{"engine/models/box.dat"},
		std::vector<std::string>{"engine/models/tet.dat"},
		std::vector<std::string>{"engine/models/skybox.dat"}
	};

	texture textures[9] = {
		std::vector<std::string>{"engine/textures/white.png"},
		std::vector<std::string>{"engine/textures/black.png"},
		std::vector<std::string>{"engine/textures/brown.png"},
		std::vector<std::string>{"engine/textures/red.png"},
		std::vector<std::string>{"engine/textures/orange.png"},
		std::vector<std::string>{"engine/textures/yellow.png"},
		std::vector<std::string>{"engine/textures/green.png"},
		std::vector<std::string>{"engine/textures/blue.png"},
		std::vector<std::string>{"engine/textures/earth.png"}
	};

	playercraft player;
	player.mod = &models[2];
	player.tex = &textures[5];
	player.bulletprefab.mod = &models[1];
	player.bulletprefab.tex = &textures[0];
	player.bulletprefab.tform.scale = { .05, .3, .05 };
	player.bulletprefab.tform.vel.y = 70;
	player.bulletprefab.isactive = true;
	engine::scene.add(&player);

	asteroid asteroidprefab;
	asteroidprefab.mod = &models[0];
	asteroidprefab.tex = &textures[2];
	asteroidprefab.tform.loc.y = 20;
	asteroidprefab.tform.vel.y = -20;
	asteroidprefab.player = &player;
	asteroid asteroids[10];
	spawnasteroids(asteroidprefab, asteroids, 10);

	enemycraft enemycraftprefab;
	enemycraftprefab.mod = &models[2];
	enemycraftprefab.tex = &textures[3];
	enemycraftprefab.tform.loc.y = 20;
	enemycraftprefab.tform.vel.y = -20;
	asteroidprefab.player = &player;
	enemycraft enemies[10];
	spawnenemies(enemycraftprefab, enemies, 10);

	playarea playarea;
	playarea.asteroids = asteroids;
	playarea.nasteroids = 10;
	playarea.enemies = enemies;
	playarea.nenemies = 10;
	playarea.player = &player;
	playarea.mod = &models[3];
	playarea.tex = &textures[0];
	playarea.tform.scale = { 20, 20, 20 };
	engine::scene.add(&playarea);

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
	
	engine::camera.tform.loc.z = 50;
	engine::camera.setdebug(false);

	engine::start();

	return 0;
}