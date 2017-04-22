// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

#version 430

// Uniforms
layout (location = 3) uniform mat4 modelWorld;
layout (location = 4) uniform mat4 worldView;

// Attributes
layout (location = 0) in vec3 modelLoc;
layout (location = 1) in vec2 modelUV;
layout (location = 2) in vec3 modelNorm;

// Varyings
out vec3 loc;
out vec2 uv;
out vec3 norm;

void main()
{
	// World space
	loc = (modelWorld * vec4(modelLoc, 1)).xyz;
	uv = modelUV;
	norm = normalize((transpose(inverse(modelWorld)) * vec4(modelNorm, 0)).xyz);

	// View space
	gl_Position = worldView * vec4(loc, 1);
}