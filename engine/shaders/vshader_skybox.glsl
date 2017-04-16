// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

#version 430

// Model space
layout (location = 0) in vec3 modelLoc;

// Model-world-view transforms
layout (location = 4) uniform mat4 worldView;

out vec3 texdir;

void main()
{
	// cubemap skybox texture coordinate is a direction
	//texdir = vec3(modelLoc.x, modelLoc.y, modelLoc.z);
	texdir = modelLoc;

	// Transform from model space into view space
	gl_Position = worldView * vec4(modelLoc, 1);
}