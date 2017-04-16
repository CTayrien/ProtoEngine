// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

#version 430

uniform samplerCube myCubemap;

in vec3 texdir;

out vec4 fragColor;

void main()
{
	fragColor = texture(myCubemap, texdir);
}