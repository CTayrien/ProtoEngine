#pragma once
#include "object.h"

class builder :
	public object
{
public:
	/*static object* theearth;
	static object* resources;
	static int numresources;*/

	float maxvelocity = 1.0f;

	object* findNearestRes();

	builder();
	builder(model* mod, texture* tex);

	~builder() override;

	void script() override;
};

