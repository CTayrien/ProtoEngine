#include "Globe.h"

Globe::Globe()
{
	this->tex = new texture("planet/earth.png");
	this->mod = new model("engine/models/sphere.dat");
}

Globe::~Globe()
{
	delete tex;
	delete mod;
}

void Globe::update()
{
	tform.update();
}
