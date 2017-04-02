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
	// Read from HD
	modelBytes = fileio::read(filename.c_str());

	// Process
	//if (filename == "engine/models/sphere.dat") {
		processdat();
	//}
	//else {
		//process();
	//}

	// Write to vram
	upload();

	delete[] modelBytes;

	loaded = true;
}

void model::processobj()
{
	// process data
	if (modelBytes == nullptr) return;
	std::stringstream modelData(modelBytes);	// copies the data to another location on the heap and wraps it... lame.
	
	using glm::vec2;
	using glm::vec3;
	using std::vector;
	using std::string;

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

	// Recenter model
	glm::vec3 min, max, c;
	min = max = locs[0];
	for (uint32_t i = 1; i < locs.size(); i++) {
		for (int j = 0; j < 3; j++) {
			if (locs[i][j] < min[j]) min[j] = locs[i][j];
			if (locs[i][j] > max[j]) max[j] = locs[i][j];
		}
	}
	c = (min + max) / 2.f;
	for (uint32_t i = 0; i < locs.size(); i++) {
		locs[i] -= c;
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

	vertBufDataPtr = (void*)(&(vertBufData[0].loc.x));
}

void model::processdat()
{
	if (modelBytes == nullptr) return;

	// set up addresses
	float* maxxptr = (float*)modelBytes;
	float* maxyptr = ((float*)modelBytes) + 1;	// 4 bytes
	float* maxzptr = ((float*)modelBytes) + 2;	// 8 bytes
	uint32_t* nvertptr = (uint32_t*)(modelBytes + 12);

	float* vbufdatptr = (float*)(modelBytes + 16);

	// try to deref
	max.x = *maxxptr;
	max.y = *maxyptr;
	max.z = *maxzptr;
	nverts = *nvertptr;

	vertBufDataPtr = (void*)(vbufdatptr);

	//vertBufData.resize(nverts);
	//for (uint32_t i = 0; i < nverts; i++) {
	//	vertBufData[i].loc.x = *(vbufdatptr + 0);
	//	vertBufData[i].loc.y = *(vbufdatptr + 1);
	//	vertBufData[i].loc.z = *(vbufdatptr + 2);
	//
	//	vertBufData[i].uv.x = *(vbufdatptr + 3);
	//	vertBufData[i].uv.y = *(vbufdatptr + 4);
	//
	//	vertBufData[i].norm.x = *(vbufdatptr + 5);
	//	vertBufData[i].norm.y = *(vbufdatptr + 6);
	//	vertBufData[i].norm.z = *(vbufdatptr + 7);
	//
	//	vbufdatptr += 8;
	//}
}

void model::upload()
{
	// Vertex array
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Buffer model data
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertex) * nverts,
		vertBufDataPtr,//&vertBufData[0],
		GL_STATIC_DRAW);
	vertBufData.clear();

	// Vertex attributes for model loc, uv, norm
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)sizeof(glm::vec3));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
