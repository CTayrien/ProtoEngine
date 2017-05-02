/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#pragma once
#include <map>

class asset
{
public:
	// Using pointers allows polymorphism to work - stores address of first asset to load - subsequent assets with same name copy its data - may become invalid if first asset moves or is deleted (when would it? can the map store its own?)
	static std::map<std::string, asset*> manager;
	
	std::string filename;
	bool loaded = false;

	asset(std::string filename);
	virtual ~asset();

	void tryload();
	virtual bool load() = 0;
	virtual void unload() = 0;
 };