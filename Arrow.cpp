#include "Arrow.h"



Arrow::Arrow()
{
	mod = new model("engine/models/arrow.dat");
	tex = new texture("engine/textures/red.png");
}


Arrow::~Arrow()
{
	delete mod;
	delete tex;
}

void Arrow::update()
{
	tform.update();
}
