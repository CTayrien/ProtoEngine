#include "moon.h"

moon::moon()
{
}

moon::moon(model * mod, texture * tex)
{
	this->mod = mod;
	this->tex = tex;
}

moon::~moon()
{
}

void moon::update()
{
	tform.derivematrix();
}