/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#pragma once
#include "Arrow.h"

class slerparrow :
	public Arrow
{
public:
	transform* a;
	transform* b;
	transform* qtvector, *qavector, *qbvector;// , *derper, *qdvector;
	
	float f = 1.0f / 3.0f;		// slerp frequency (hz)
	float t = 0.0f;				// current t
	float d = 1.0f;				// current direction
	bool go = true;

	slerparrow();
	~slerparrow();

	void script() override;
};