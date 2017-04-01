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
	glm::mat4 worldView;

	float fov; //fov init in ctor
	float aspect = (float)window::w / (float)window::h;
	float zNear = .01f;
	float zFar = 1000.f;
	
	const float maxspeed = 2.f;
	const float sens = .005f;
	
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