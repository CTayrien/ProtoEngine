#include "builder.h"
#include <glm\glm.hpp>

object * builder::findNearestRes()
{
	//float dist = 1/0;
	//float dist = FLT_MAX;
	float dist = 100000000;
	object* nearest = nullptr;

	//for (int i = 0; i < numresources; i++) {
	//	float newdist = glm::distance(resources[i].tform.loc , tform.loc);
	//	
	//	if (dist > newdist) {
	//		dist = newdist;
	//		nearest = resources + i;
	//	}
	//}

	return nearest;
}

builder::builder()
{
	tform.scale *= 4;
	tform.loc = { .5, 0, 0 };
}

builder::builder(model * mod, texture * tex)
{
	this->mod = mod;
	this->tex = tex;

	tform.scale *= 4;
	tform.loc = { .5, 0, 0 };
}

builder::~builder()
{
}

void builder::update()
{
	tform.update();

	//findNearestRes();
	// init static data, how does a normal design pattern do this
	// move toward nearest resource with max velocity.
	// ????
	// MAKE A CASTLE!!!
}