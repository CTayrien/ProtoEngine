// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

#version 430

// Model space
layout (location = 0) in vec3 modelLoc;

// Model-world-view transforms
layout (location = 5) uniform mat4 worldView;
layout (location = 6) uniform vec3 camloc;

out vec3 texdir;

void main()
{
	// Cubemap skybox texture coordinate is a direction
	texdir = modelLoc;

	// Transform from model space into view space - cubemap doesn't rotate or scale, and if camera is at origin, then cubemap translation is 0 too:  as long as camera is located at origin, cubemap model-world is identity, implicitly included in the transformation below.
	gl_Position = worldView * vec4(modelLoc + camloc, 1);
}