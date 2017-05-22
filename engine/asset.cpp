/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "asset.h"
#include <fstream>

std::map<std::string, asset*> asset::assets;

char * asset::read(const char * filename)
{
	// Open
	std::ifstream is(filename, std::ios::binary);
	if (!is.is_open()) return 0;

	// Length
	is.seekg(0, std::ios::end);
	int length = (int)is.tellg();
	is.seekg(0, std::ios::beg);

	// Read & close
	char* bytes = new char[length + 1];
	bytes[length] = 0;
	is.read(bytes, length);
	is.close();

	return bytes;
}

asset::asset()
{
}

asset::asset(std::vector<std::string> filenames)
{
	this->filenames = filenames;
	for (auto& file : filenames) {
		key += file + " ";
	}
}

asset::~asset()
{
}