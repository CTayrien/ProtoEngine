/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

// Project & Engine Description:
// Create a scene/game using prototype game engine "Proto Engine"
// This engine is designed for easily building prototypes of games.
// Certain functionalities are not available, such as skeletal/spritesheet animation, sound, networking, quaternions, input event handling, etc.
// If dozens of game objects are used, framerate may begin to drop below 60fps on modern hardware.

// Example Directions
// 1) Create a VS project. Install GLEW, GLFW, FreeImage and GLM. Add additional linker dependencies: glew32.lib, opengl32.lib, glfw3.lib, FreeImage.lib. Add include directory: $(ProjectDir)engine.

// 2) Add a scene.cpp and include engine.h.
#include "engine/engine.h"
#include <thread>

// 3) Develop assets (models and textures) for game objects, put their behavior in a new obj, and include the object's header.

// 4) Declare assets and objects globally, on the stack, or on the heap.
//		Use c'tors or setters to ensure the member data is initialized for game objects and assets before loading, updating or rendering.  
#include "planet/planet.h"
model sphereMod("engine/models/sphere.obj");
texture earthTex("engine/textures/earth.png");
planet earth(&sphereMod, &earthTex);

#include "spacecraft/spacecraft.h"
model spacecraftMod("spacecraft/Mars Lander Space Capsule tri.obj");
//"Mars_Lander_Space_Capsule.mtl"
//texture ab1.jpg // mtl file refers to these two textures
//texture cp2.jpg //
texture blackTex("engine/textures/black.png");
spacecraft spacecraftObj(&spacecraftMod, &blackTex);

#include "moon/moon.h"
texture moonTex("moon/moon.png");
const int maxmoons = 60;
int nmoons = 0;
moon moons[maxmoons];

void spawnMoons() {
	int i = 0;

	moons[i].mod = &sphereMod;
	moons[i].tex = &moonTex;
	moons[i].tform.loc.x = 5;

	nmoons++;
}

#include "builder/builder.h"
model antMod("builder/ant.obj");
//texture blackTex("engine/textures/black.png");
int nbuilders = 0;
const int maxbuilders = 60;
builder builders[maxbuilders];

void spawnbuilder() {
	if (nbuilders >= maxbuilders)
		return;

	int i = nbuilders++;
	
	builders[i].mod = &antMod;
	builders[i].tex = &blackTex;

	if (i > 0) {
		builders[i].tform = builders[i-1].tform;
		builders[i].tform.loc.z += .025;
	}
}

void loadassets() {
	sphereMod.load();
	earthTex.load();

	moonTex.load();

	spacecraftMod.load();

	antMod.load();
	blackTex.load();
}

void unloadassets() {
	sphereMod.unload();
	earthTex.unload();

	moonTex.unload();

	spacecraftMod.unload();

	antMod.unload();
	blackTex.unload();
}

int main() {
	// 5) Init engine. (libraries, window, renderer, input, physics, etc. - start before calling anything else - constructors are fine as long as they don't interact with the engine
	if (!engine::start()) return 1;

	// 6) Load all assets. (Load each asset only once and reuse each when possible)
	//std::thread loader(loadassets);
	loadassets();

	spawnMoons();

	for (int i = 0; i < maxbuilders; i++) {
		spawnbuilder();
	}

	for (int i = 0; i < maxbuilders; i++) {
		earth.push(builders+i);
	}

	engine::time.update();

	// 7) Loop while the escape key isn't pressed
	while (!input::isDown(input_esc))
	{
		// 8) Update engine. (More efficient systems may be developed (spatial partitioning, render lists, instanced rendering, frustum culling, multithreading, etc.))
		engine::update();
		
		// 9) Update all objects
		earth.update();
		spacecraftObj.update();
		for (int i = 0; i < nbuilders; i++) {
			builders[i].update();
		}
		for (int i = 0; i < nmoons; i++) {
			moons[i].update();
		}

		// 10) Render all objects
		earth.render();
		spacecraftObj.render();
		for (int i = 0; i < nbuilders; i++) {
			builders[i].render();
		}
		for (int i = 0; i < nmoons; i++) {
			moons[i].render();
		}
	}
	
	// 11) Unload all assets
	//loader.join();
	unloadassets();
	
	// 12) Stop the engine
	engine::stop();

	return 0;
}