/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "model.h"
#include "fileio.h"
#include "engine.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

model::model(std::string filename)
	:asset(filename)
{
}

model::~model()
{
}

bool model::load()
{
	GLsizei locsize = sizeof(glm::vec3);
	GLsizei uvsize = sizeof(glm::vec2);
	GLsizei normsize = sizeof(glm::vec3);
	GLsizei vertsize = locsize + uvsize + normsize;
	
	// Open & read file & allocate on heap
	char* modelBytes = fileio::read(filename.c_str());
	if (modelBytes == nullptr) return false;

	// Process file data
	max.x =	*((float*)(modelBytes + 0));
	max.y =	*((float*)(modelBytes + 4));
	max.z =	*((float*)(modelBytes + 8));
	r =		*((float*)(modelBytes + 12));
	nverts = *((uint32_t*)(modelBytes + 16));
	void* vdata = (void*)(modelBytes + 20);

	// Upload buffer data to vram
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertsize * nverts, vdata, GL_STATIC_DRAW);

	// Clear ram
	delete[] modelBytes;

	// VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Loc
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertsize, (GLvoid*)0);

	// uv
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertsize, (GLvoid*)locsize);

	// Norm
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertsize, (GLvoid*)(locsize + uvsize));

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

void model::unload()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	vao = vbo = 0;
	nverts = 0;

	max = {};
	r = 0;

	loaded = false;
}