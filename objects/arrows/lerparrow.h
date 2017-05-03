/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#pragma once
#include "Arrow.h"

class lerparrow :
	public Arrow
{
public:
	transform* a;
	transform* b;
	float f = 1.0f / 3.0f;
	float t = 0.0f;
	float d = 1.0f;
	bool go = true;

	lerparrow();
	~lerparrow();
	void script() override;
};

