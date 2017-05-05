/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include "asset.h"

#include <glm\glm.hpp>

#include <string>

class model
	: public asset
{
public:
	// Render data
	uint32_t vao = 0, vbo = 0, nverts = 0;
	
	// Half-width of tightest fit model-oriented bounding box (OBB)
	glm::vec3 max = {};

	// Radius of the tightest fit bounding sphere
	float r;

	model(std::string filename);
	~model();

	bool load() override;
	void unload() override;
};