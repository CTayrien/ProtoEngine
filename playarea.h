/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"
#include "asteroid.h"
#include "playercraft.h"
#include "enemycraft.h"

class playarea :
	public object
{
public:
	asteroid* asteroids = nullptr;
	int nasteroids = 0;

	playercraft* player = nullptr;
	
	enemycraft* enemies = nullptr;
	int nenemies = 0;
	
	playarea();
	~playarea();

	void render() override;
	bool load() override;
	void script() override;
};