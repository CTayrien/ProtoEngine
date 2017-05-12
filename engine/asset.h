/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#pragma once
#include <map>
#include <vector>
#include <string>
 
class asset
{
public:
	// Using pointers allows polymorphism to work - owns (on the heap) a copy of the first asset to load. subsequent assets with same key copy its data
	static std::map<std::string, asset*> assets;
	static char* read(const char* filename);

	std::string key;
	std::vector<std::string> filenames;
	bool loaded = false;

	asset(std::vector<std::string> filenames);
	virtual ~asset();

	virtual bool load() = 0;
	virtual void unload() = 0;
 };