#include "spacecraft.h"



spacecraft::spacecraft()
{
}

spacecraft::spacecraft(model * mod, texture * tex)
{
	this->mod = mod;
	this->tex = tex;
	tform.loc.y = 1;
	tform.scale *= .001f;
}

spacecraft::~spacecraft()
{
}

void spacecraft::update()
{
	tform.derivematrix();
}
