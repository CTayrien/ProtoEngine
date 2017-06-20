/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include "object.h"

#include <string>

class camera :
	public object
{
private:
	glm::mat4 perspective;	// break this into consituents so i can change zoom
	
public:
	float maxspeed = 2.f;
	const float sens = .005f;
	
	camera();
	~camera() override;

	bool load() override;
	void uploadpov();
	
	void script() override;
	bool isdebug = false;
	bool ispov = true;
	
	void toggledebug();
	void setdebug(bool isdebug);
	void debugmove();
	void debugturn();
};