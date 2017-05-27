/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include <vector>
#include <string>
#include <iostream>
#include "engine.h"

#include "gravaball.h"

int main()
{
	/*	Future work:

		Compelling Problems and Visuals
	smart ptr asset mngmnt, multithreading, imgui, collision system w/ struct, quat moment tensor torque, 

		AI Objects Challenges
	flocking, docking, sakura, fireworks, glow vapor trail, atoms, Optrix, astroadaptation game (time travel?)

		Physics Challenges
	predictor-corrector (L or H?), swept volume, collision manifold & reaction, 
	n-body, astrodynamics, relativity, electrodynamics, quantum, 
	
		Engine Dev (Delegate)
	game engine: sound, animation, spritesheet, networking, nsight, gpu physics
	graphics optimization: element array rendering, instanced rendering, render lists, deferred shading, shadows, crepuscular rays, lens flare, HDR, bloom, 
	
	*/

	std::vector<std::pair<std::string, void (*)()>> games =
	{
		{ "Grav-a-ball", &gravaball }
		// Developers: Add more scenes here
	};

	printf("Welcome to Proto Engine\n\nFree open-source educational prototype game engine for prototyping simple games\n\nPress ~ to toggle WASD-bound debug camera\n");

	bool invalid = true, quit = false;
	do
	{
		printf("\nPlay a game!\n");
		for (size_t i = 0; i < games.size(); i++)
			printf("    %d) %s\n", i, games[i].first.c_str());
		printf("   -1) quit\n\n");

		int num;
		std::cin >> num;
		std::cin.ignore();

		if (num == -1) {
			quit = true;
		}
		else if (num < 0 || num > games.size() - 1) {
			printf("Error with num: %d\n", num);
		}
		else if (games[num].second) {
			(*games[num].second)();
			invalid = false;
		}
		else {
			printf("Null scene pointer: %s\n", games[num].first.c_str());
		}
	} while (invalid && !quit);

	if (!quit)
		engine::start();

	return 0;
}