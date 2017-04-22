#include "lerparrow.h"
#include "engine\engine.h"


lerparrow::lerparrow()
{
}


lerparrow::~lerparrow()
{
}

void lerparrow::update()
{
	// try to stop
	if (go) {
		if (d > 0.0f && t > 1.0f) {
			d = -1.0f;
			go = false;
		}
		if (d < 0.0f && t < 0.0f) {
			d = 1.0f;
			go = false;
		}
	}
	// try to start
	if (!go) {
		if (input::isDown(input_enter)) {
			go = true;
		}
	}

	if (go) {
		t += d * f * engine::time.dt;
	}

	tform.rot = a->rot * t + b->rot * (1.0f - t);

	tform.update();
}
