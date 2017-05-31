/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include <vector>
#include <string>
#include <iostream>
#include "engine.h"

#include "gravaball.h"
#include "pong.h"
#include "demoquat.h"
#include "atoms.h"
#include "orbits.h"
#include "wrecksite.h"
// Developers: Add more scenes here

// Call a scene building function and then engine::start. Prompt user to choose which scene. Should multithread, start engine first, and put this menu in imgui.
int main()
{
	std::vector<std::pair<std::string, void (*)()>> scenelist =
	{
		{ "Grav-a-ball", &gravaball },
		{ "Pong", &pong },
		{ "Demo Qaternions", &demoquat },
		{ "Atoms", &atoms },
		{ "Orbits", &orbits },
		{ "Wrecksite", &wrecksite }
		// Developers: Add more scenes here
	};

	printf("Welcome to Proto Engine\n\nFree open-source educational prototype game engine for prototyping simple games\n\nPress ~ to toggle WASD-bound debug camera\n");

	bool quit = false;
	do {
		printf("\nBuild a scene\n");
		printf("    0) Quit\n");
		for (size_t i = 0; i < scenelist.size(); i++)
			printf("    %d) %s\n", i+1, scenelist[i].first.c_str());

		int num;
		std::cin >> num;
		num--;
		std::cin.ignore();

		if (num == -1) {
			quit = true;
		}
		else if (num < -1 || num > scenelist.size() - 1) {
			printf("Error: num < 0 or num > %d\n", scenelist.size());
		}
		else if (nullptr == scenelist[num].second) {
			printf("Error: Scene building func is null pointer: %s\n", scenelist[num].first.c_str());
		}
		else {
			(*scenelist[num].second)();
			engine::start();
			break;
		}
	} while (!quit);

	printf("Press enter to exit");
	std::cin.get();
	return 0;
}