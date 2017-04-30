/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include <glm\glm.hpp>

#include <string>

class model
{
private:
	uint32_t vao = 0, vbo = 0, nverts = 0;

public:
	std::string filename = "default model";
	
	// Half-width of tightest fit model-oriented bounding box (OBB)
	glm::vec3 max = {};

	// Radius of the tightest fit bounding sphere
	float r;

	model(std::string filename);
	~model();

	// Load before rendering, after engine starts
	void load();
	bool loaded = false;
	
	// Render after loading
	void render();
	
	// Unload when done with the model
	void unload();
};