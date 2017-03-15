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
#include "objecta/objecta.h"

// 4) Declare assets and objects globally, on the stack, or on the heap.
//		Use c'tors or setters to ensure the member data is initialized for game objects and assets before loading, updating or rendering.
model mod("engine/models/sphere.obj");
texture tex("engine/textures/earth.png");
objecta myobja(&mod, &tex);

int main() {
	// 5) Init engine. (libraries, window, renderer, input, physics, etc. - start before calling anything else - constructors are fine as long as they don't interact with the engine
	if (!engine::start()) return 1;

	// 6) Load all assets. (Load each asset only once and reuse each when possible)
	if (!mod.load()) return 1;
	if (!tex.load()) return 1;

	// 7) Loop while the escape key isn't pressed
	while (!input::isDown(input_esc))
	{
		// 8) Update engine. (More efficient systems may be developed (spatial partitioning, render lists, instanced rendering, frustum culling, multithreading, etc.))
		engine::update();
		
		// 9) Update all objects
		myobja.update();

		// 10) Render all objects
		myobja.render();
	}
	
	// 11) Unload all assets
	mod.unload();
	tex.unload();
	
	// 12) Stop the engine
	engine::stop();

	return 0;
}