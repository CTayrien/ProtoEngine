/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "light.h"
#include <GL\glew.h>

light::light()
{
	tform.loc = { 10 , 0, 0 };
}

light::~light()
{
}

void light::script()
{
	// Upload uniform lighting data
	glUniform3fv(5, 1, &tform.loc[0]);
}