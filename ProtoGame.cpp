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

// 3) Develop assets (models and textures) for game objects, put their behavior in a new obj, and include the object's header.

// 4) Declare assets and objects globally, on the stack, or on the heap.
//		Use c'tors or setters to ensure the member data is initialized for game objects and assets before loading, updating or rendering.  
#include "planet/planet.h"
model sphereMod("engine/models/sphere.obj");
texture earthTex("engine/textures/earth.png");
planet earth(&sphereMod, &earthTex);

//void earthinit(object* objs, int n) {
//	memccpy(earth->objs, objs, 0, n * 4);
//};

#include "builder/builder.h"
model antMod("builder/ant.obj");
texture blackTex("engine/textures/black.png");
int nbuilders = 0;
const int maxbuilders = 10;
builder builders[maxbuilders];

void spawnbuilder() {
	if (nbuilders >= maxbuilders)
		return;

	int i = nbuilders++;
	
	builders[i] = builder(&antMod, &blackTex);
	builders[i].tform.vel.z = 1;
}

int main() {
	// 5) Init engine. (libraries, window, renderer, input, physics, etc. - start before calling anything else - constructors are fine as long as they don't interact with the engine
	if (!engine::start()) return 1;

	// 6) Load all assets. (Load each asset only once and reuse each when possible)
	if (!sphereMod.load()) return 1;
	if (!earthTex.load()) return 1;

	if (!antMod.load()) return 1;
	if (!blackTex.load()) return 1;

	spawnbuilder();

	// 7) Loop while the escape key isn't pressed
	while (!input::isDown(input_esc))
	{
		// 8) Update engine. (More efficient systems may be developed (spatial partitioning, render lists, instanced rendering, frustum culling, multithreading, etc.))
		engine::update();
		
		// 9) Update all objects
		earth.update();
		for (int i = 0; i < nbuilders; i++) {
			builders[i].update();
		}

		// 10) Render all objects
		earth.render();
		for (int i = 0; i < nbuilders; i++) {
			builders[i].render();
		}
	}
	
	// 11) Unload all assets
	sphereMod.unload();
	earthTex.unload();
	antMod.unload();
	blackTex.unload();
	
	// 12) Stop the engine
	engine::stop();

	return 0;
}