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
#include "globe/Globe.h"
Globe globe;

#include "arrows/Arrow.h"
Arrow beijing;
Arrow nyc;

//#include "arrows/lerparrow.h"
//lerparrow lerper;

#include "arrows/slerparrow.h"
slerparrow slerper;

Globe qtvector;

int main() {
	// 5) Init engine. (libraries, window, renderer, input, physics, etc. - start before calling anything else - constructors are fine as long as they don't interact with the engine
	renderer::thematerial.ambDifSpec[0] = .9f;	//lighten up a bit
	if (!engine::start()) return 1;

	// 6) Load all assets. (Load each asset only once and reuse each when possible)
	globe.load();
	globe.tform.rot.y = -125.0f * engine::pi / 180.f;

	beijing.load();
	beijing.tform.rot.y = -100.f * engine::pi / 180.f;	//yaw = longitude
	beijing.tform.rot.x = 40.f * engine::pi / 180.f;	//pitch = latitude
	
 	nyc.load();
	nyc.tform.rot.y = 70.f * engine::pi / 180.f;	//yaw = longitude
	nyc.tform.rot.x = 40.f * engine::pi / 180.f;	//pitch = latitude
	
	// need a screw model and a set-forward vector so i can direct it outward from the sphere

	//nyc.tform.rot.z = 90.f * engine::pi / 180.f;

	//lerper.load();
	//lerper.a = &beijing.tform;
	//lerper.b = &nyc.tform;

	delete qtvector.tex;
	qtvector.tex = new texture("engine/textures/blue.png");
	delete qtvector.mod;
	qtvector.mod = new model("bolt.dat");
	qtvector.load();
	qtvector.tform.scale *= 1.0f/3000.0f;
	qtvector.tform.updatematrix();

	delete slerper.mod;
	slerper.mod = new model("spacecraft/spacecraft.dat");
	slerper.load();
	slerper.a = &beijing.tform;
	slerper.b = &nyc.tform;
	slerper.qtvector = &qtvector.tform;
	slerper.tform.scale = glm:: vec3(1.0f) / 300.0f;
	slerper.tform.updatematrix();

	// 7) Loop while the escape key isn't pressed
	while (!input::isDown(input_esc))
	{
		// 8) Update engine. (More efficient systems may be developed (spatial partitioning, render lists, instanced rendering, frustum culling, multithreading, etc.))
		engine::update();

		// 9) Update all objects
		beijing.update();
		nyc.update();
		//lerper.update();
		slerper.update();
		//qtvector.update();
		//globe.update();

		// 10) Render all objects
		beijing.render();
		nyc.render();
		//lerper.render();
		qtvector.render();
		slerper.render();
		globe.render();
	}

	// 11) Unload all assets
	globe.unload();
	beijing.unload();
	nyc.unload();
	slerper.unload();

	// 12) Stop the engine
	engine::stop();

	return 0;
}