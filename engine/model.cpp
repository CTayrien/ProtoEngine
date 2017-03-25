/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "model.h"
#include "fileio.h"

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

bool model::load()
{
	using glm::vec2;
	using glm::vec3;
	using std::vector;
	using std::string;

	struct Vertex { vec3 loc; vec2 uv; vec3 norm; };
	struct VertInd { uint32_t locInd, uvInd, normInd; };

	// Read file
	char* contents = fileio::read(filename.c_str());
	if (contents == nullptr) return false;
	std::stringstream modelData(contents);	// copies the data to another location on the heap and wraps it... lame.
	delete[] contents;						// deletes one copy of the data from the heap... lame.

	vector<Vertex> vertBufData;

	// Get unique vertex locs, uvs and norms
	vector<vec3> locs;
	vector<vec2> uvs;
	vector<vec3> norms;

	// Get indices of locations, uvs and normals for stitching
	vector<VertInd> vertInds;

	// The following will be parsed from the file...
	Vertex vertex;
	VertInd vertInd;
	char slash;

	// Get all lines from the file, one at a time.
	string lineString;
	while (std::getline(modelData, lineString)) {

		// Make the current line into a stringstream so it can be parsed.
		std::stringstream stream(lineString);

		// Parse label
		string label;
		stream >> label;

		// Parse and add a loc
		if (label == "v") {
			stream >> vertex.loc.x >> vertex.loc.y >> vertex.loc.z;
			locs.push_back(vertex.loc);
		}
		// Parse and add a uv
		if (label == "vt") {
			stream >> vertex.uv.x >> vertex.uv.y;
			uvs.push_back(vertex.uv);
		}
		// Parse and add a norm
		if (label == "vn") {
			stream >> vertex.norm.x >> vertex.norm.y >> vertex.norm.z;
			norms.push_back(vertex.norm);
		}
		// Parse and add 3 complex vertInds
		if (label == "f") {
			for (int i = 0; i < 3; i++) {
				stream >> vertInd.locInd >> slash >> vertInd.uvInd >> slash >> vertInd.normInd;
				vertInds.push_back({ vertInd.locInd - 1, vertInd.uvInd - 1, vertInd.normInd - 1 });
			}
		}
	}

	// Get max extremeties (needed for collision checks)
	for (uint32_t i = 0; i < locs.size(); i++) {
		glm::vec3 sqrd = locs[i] * locs[i];
		float r = glm::sqrt(sqrd.x + sqrd.y + sqrd.z);
		glm::vec3 abs = glm::sqrt(sqrd);

		//if (r > maxr) maxr = r;
		if (abs.x > max.x) max.x = abs.x;
		if (abs.y > max.y) max.y = abs.y;
		if (abs.z > max.z) max.z = abs.z;
	}

	// Stitch together data for vertex buffer
	nverts = vertInds.size();
	vertBufData.resize(nverts);
	for (uint32_t i = 0; i < nverts; i++) {
		vertBufData[i].loc = locs[vertInds[i].locInd];
		vertBufData[i].uv = uvs[vertInds[i].uvInd];
		vertBufData[i].norm = norms[vertInds[i].normInd];
	}

	// Vertex array
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Buffer model data
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertex) * nverts,
		&vertBufData[0],
		GL_STATIC_DRAW);

	// Vertex attributes for model loc, uv, norm
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), 0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)sizeof(vec3));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)(sizeof(vec3) + sizeof(vec2)));

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE,
	//	sizeof(Vertex), 0);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
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

	vao = vbo = -1;
	nverts = 0;
}
