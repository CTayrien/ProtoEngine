/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"
#include "window.h"

#include <string>

class camera :
	public object
{
private:
	std::string varname = "worldView";
	int id = 4;

	//float aspect = 800.f / 600.f;	//(float)windowSize.x / (float)windowSize.y,
	float fov = glm::pi<float>() * .4f;
	float aspect = (float)window::w / (float)window::h;
	float zNear = .01f;
	float zFar = 1000.f;
	
	const float maxvel = 2.f;
	const float sens = .005f;
	
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;

	glm::mat3 R;
	glm::mat4 worldView;

public:
	camera();
	~camera() override;

	bool start();
	void update() override;
	void upload();
	void move();
	void turn();
	void stop();
};