/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "asset.h"

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

std::map<std::string, asset*> asset::manager;

asset::asset(std::string filename)
{
	this->filename = filename;
}

asset::~asset()
{
}

void asset::tryload()
{
	if (!loaded) {
		if (manager[filename]) {
			*this = *manager[filename];	//polymorphism (fail)/(win)?
		}
		else {
			loaded = load();
			if (loaded) {
				manager[filename] = this;	//polymorphism (fail)/(win)?
				// if the asset moves, this is bad
				// if we copy the contents, polymorphism fails
				// if we create a copy on the heap ... how can polymorphism work??
			}
		}
	}
}