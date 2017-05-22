/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "engine.h"
#include <vector>
#include <string>
#include <iostream>

#include "gravaball.h"

int main()
{
	std::vector<std::pair<std::string, void (*)()>> games =
	{
		{ "Grav-a-ball", &gravaball }
		// Developers: Add more scenes here
		// flocking (& docking?), fluids & softbody,
	};

	printf("Welcome to Proto Engine\n\nfree open-source educational prototype game engine for prototyping simple games\n");

	bool invalid = true, quit = false;
	do
	{
		printf("\nPlay a game!\n");
		for (size_t i = 0; i < games.size(); i++)
			printf("    %d) %s\n", i, games[i].first.c_str());
		printf("   -1) quit\n\n");

		int num;
		std::cin >> num;

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