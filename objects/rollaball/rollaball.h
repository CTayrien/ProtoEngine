/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"

class rollaball :
	public object
{
public:
	int score = 0;

	void script() override;
	rollaball();
	~rollaball();
};

