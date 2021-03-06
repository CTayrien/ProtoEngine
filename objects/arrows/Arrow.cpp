/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "Arrow.h"

Arrow::Arrow()
{
	mod = model({ "engine/models/arrow.dat" });
	tex = texture({"engine/textures/white.png"});
	tform.scale.x *= .1f;
	tform.scale.y *= .1f;
	tform.scale.z *= 1.1f;
	//tform.derivematrix();
}

Arrow::~Arrow()
{
}

void Arrow::script()
{
	//tform.derivematrix();
}