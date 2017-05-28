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
	

	std::vector<std::pair<std::string, void (*)()>> scenelist =
	{
		{ "Grav-a-ball", &gravaball }
		// Developers: Add more scenes here
	};

	printf("Welcome to Proto Engine\n\nFree open-source educational prototype game engine for prototyping simple games\n\nPress ~ to toggle WASD-bound debug camera\n");

	// Chose a scene from the list, then start engine. Should multithread, start engine first, and put this menu in imgui.
	bool invalid = true, quit = false;
	do {
		printf("\nBuild a scene\n");
		for (size_t i = 0; i < scenelist.size(); i++)
			printf("    %d) %s\n", i, scenelist[i].first.c_str());
		printf("   -1) quit\n\n");

		int num;
		std::cin >> num;
		std::cin.ignore();

		if (num == -1) {
			quit = true;
		}
		else if (num < -1 || num > scenelist.size() - 1) {
			printf("Error: num < -1 or num > %d\n", scenelist.size() - 1);
		}
		else if (nullptr == scenelist[num].second) {
			printf("Error: Scene building func is null pointer: %s\n", scenelist[num].first.c_str());
		}
		else {
			// Build scene with function that calls engine.spawn, etc
			(*scenelist[num].second)();
			invalid = false;
		}
	} while (invalid && !quit);

	if (!quit)
		engine::start();

	return 0;
}