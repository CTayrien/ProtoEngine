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
	
	const float maxspeed = 2.f;
	const float sens = .005f;
	
public:
	camera();
	~camera() override;

	void load() override;
	void uploadpov();
	
	void script() override;
	bool isdebug = true;
	bool ispov = true;
	void render() override;
	
	void toggledebug();
	void setdebug(bool isdebug);
	void debugmove();
	void debugturn();
};