/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "model.h"
#include "fileio.h"
#include "engine.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <sstream>
#include <iostream>
#include <vector>

model::model(std::string filename)
{
	this->filename = filename;
}

model::~model()
{
}

void model::load()
{
	// For Skybox, there's no uv or norm. Can this figure that out programatically?
	struct Vertex { glm::vec3 loc; glm::vec2 uv; glm::vec3 norm; };
	struct VertInd { uint32_t locInd, uvInd, normInd; };
	
	// Open & read file
	char* modelBytes = fileio::read(filename.c_str());
	if (modelBytes == nullptr) return;

	// Process file data
	max.x = *((float*)(modelBytes + 0));
	max.y = *((float*)(modelBytes + 4));
	max.z = *((float*)(modelBytes + 8));
	nverts = *((uint32_t*)(modelBytes + 12));
	void* vertBufDataPtr = (void*)(modelBytes + 16);

	// Upload buffer data to vram
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertex) * nverts,
		vertBufDataPtr,
		GL_STATIC_DRAW);

	// Clear ram
	delete[] modelBytes;

	// VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Loc
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (GLvoid*)0);

	// uv
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (GLvoid*)12);

	// Norm
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (GLvoid*)20);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	loaded = true;
}


void model::render()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, nverts);
}

void model::unload()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	vao = vbo = 0;
	nverts = 0;
}
