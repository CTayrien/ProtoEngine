#include "engine\engine.h"

int main() 
{
	engine::start();

	while (!input::isDown(input_esc)) 
	{	
		engine::update();
	}

	engine::stop();

	return 0;
}