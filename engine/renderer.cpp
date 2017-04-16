/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "engine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

shader renderer::theshader;
shader renderer::shader_skybox;

material renderer::thematerial;

bool renderer::start()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(.45f, .45f, .9f, 1.f);

	shader_skybox = shader("engine/shaders/vshader_skybox.glsl", "engine/shaders/fshader_skybox.glsl");
	if (!shader_skybox.load()) return false;
	if (!theshader.load()) return false;
	
	theshader.use();

	thematerial.use();

	return true;
}

void renderer::update()
{
	// Send color buffer to screen, clear new frame buffers
	glfwSwapBuffers(window::ptr);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Skybox shader & uniform
	shader_skybox.use();
	glm::vec3 temp = engine::cam.tform.loc;
	engine::cam.tform.loc = glm::vec3();
	engine::cam.upload();
	engine::cam.tform.loc = temp;

	// Using a special model will remedy the need for toggling cull face. The model does not need uvs and normals. A special model loader will support that.
	glDisable(GL_CULL_FACE);
	engine::skybox.render();
	glEnable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	// Update game objects, then render game objects
	theshader.use();
}

void renderer::stop()
{
	theshader.unload();
	shader_skybox.unload();
}