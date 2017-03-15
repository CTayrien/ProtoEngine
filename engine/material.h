/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

class material
{
public:
	int id = 7;
	float ambDifSpec[4] = { .1f, 1.0f, .1f, 16.f };
	
	material();
	material(float amb, float diff, float spec, float specpow);
	~material();

	void use();
};