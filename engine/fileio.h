/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include <mutex>

class fileio
{
private:
	// Allow single thread to access HD.
	static std::mutex mut;
public:
	// Loads file's bytes onto heap. Failure returns nullptr.
	static char* read(const char* filename);
};

