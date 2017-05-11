/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"
#include "playerbullet.h"

class playercraft :
	public object
{
public:
	playerbullet bulletprefab;//set up in c'tor? 
	
	playerbullet bullets[10];
	int cbullet = 0;
	int nbullets = 10;

	playercraft();
	~playercraft();

	void script() override;
};