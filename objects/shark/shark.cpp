#include "shark.h"
#include "engine.h"

shark::shark()
{
}

shark::~shark()
{
}

void shark::script()
{
	tform.loc = engine::cam.tform.loc;
	if (engine::input.ddown[input_shift]) {
		float c = 2;
		engine::cam.maxspeed *= c;
	}
}