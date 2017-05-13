/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"
#include "objects/playercraft/playercraft.h"

class enemycraft :
	public object
{
public:
	playercraft* player = nullptr;
	bool isactive = false;

	enemycraft();
	~enemycraft();

	void script() override;
};

