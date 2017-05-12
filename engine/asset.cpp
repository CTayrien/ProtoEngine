/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "asset.h"
#include <fstream>

// could add static managers map<string filename, texture>
// object constructors set asset filenames, 
//		when objects load, the assets try to load
//		if each finds its filename has already been entered in the corresponding map,
//		it copies the data of the entry in the map.
//		if not, it loads and enters itself into the map
//		the load function is specialized for each asset type
//		in the object's draw, it uses/binds/etc the assets it needs
//			this is best done with template programming?
//			asset of type texture, shader, model
//			or asset is a base class, the types are children with overriden load method?
//	the important thing is that it can copy the integer data into this object.
//		the model data should not be copied on vram
//		the map can keep track of refs
//		the map can delete it when it is done with it
//		using the right pattern, this can simplify the engine and the games
//		devs wont have to tell the assets to load or manage sharing
//		the map wont be used in real-time, only when loading
//		there's one map to assets on the heap. polymorphism allows it
//		individual new assets get pointers to objects of their own type on the heap
//		guarantee only loads each file name into vram once
//		guarantee doesn't use map during game loop
//		guarantee doesn't use much extra memory
//		guarantee it simplifies the code base
//		guarantee no object unloads resources of other objects

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