/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include <glm\glm.hpp>

#include <string>
#include <vector>

class model
{
private:
	struct Vertex { glm::vec3 loc; glm::vec2 uv; glm::vec3 norm; };
	struct VertInd { uint32_t locInd, uvInd, normInd; };
	std::vector<Vertex> vertBufData;
	char* modelBytes = nullptr;

	uint32_t vao = 0, vbo = 0, nverts = 0;

public:
	std::string filename = "default model";
	
	// e : half-width of obb (tightest fit)
	glm::vec3 max = {};
	
	// r : half-width of square AABB (loosest fit) and sphere (tighter fit)
	//float maxr = 0;

	model(std::string filename);
	~model();

	// Load before rendering, after engine starts
	void load();
	bool loaded = false;
	void process();			//should pre-process models with tool? 
	void upload();

	// Render after loading
	void render();
	
	// Unload when done with the model
	void unload();
};