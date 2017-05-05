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
	glm::mat4 perspective;
	glm::mat4 worldView;
	
	bool isfps = true;
	const float maxspeed = 2.f;
	const float sens = .005f;
	
public:
	
	camera();
	~camera() override;

	void load() override;
	void upload();
	
	void script() override;
	bool ispov = true;
	void render() override;
	
	//void toggleisfps();
	void setisfps(bool isfps);
	void flymove();
	void flyturn();
};