/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"

class satellite :
	public object
{
public:
	object* player;
	float pi = 3.14159;
	float phase = 0;
	float t = 0;
	float rorbit = 4;
	float period = 4;
	glm::vec3 c() { return player->tform.loc; }

	satellite(object* player, float phase);
	~satellite();

	void script() override;
};