/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once
#include "object.h"
#include "material.h"

class skybox
	: public object
{
private:
public:
	skybox();
	~skybox();

	bool start();

	void update() override;

	void render() override;

	void stop();
};