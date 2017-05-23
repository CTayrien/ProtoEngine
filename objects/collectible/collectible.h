/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"
#include "objects/rollaball/rollaball.h"

class collectible :
	public object
{
public:
	rollaball* player = nullptr;
	object* satellite[4];

	collectible();
	~collectible();
	void script() override;
};

