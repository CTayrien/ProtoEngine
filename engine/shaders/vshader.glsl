// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

#version 430

// Model space
layout (location = 0) in vec3 modelLoc;
layout (location = 1) in vec2 modelUV;
layout (location = 2) in vec3 modelNorm;

// Model-world-view transforms
layout (location = 3) uniform mat4 modelWorld;

layout (location = 4) uniform mat4 worldView;

// World space
out vec3 worldLoc;
out vec2 uv;
out vec3 worldNorm;

void main()
{
	// Transform from model space into world space
	worldLoc = (modelWorld * vec4(modelLoc, 1)).xyz;
	uv = modelUV;
	worldNorm = normalize((transpose(inverse(modelWorld)) * vec4(modelNorm, 0)).xyz);
	
	// Transform from world space into view space
	gl_Position = worldView * vec4(worldLoc, 1);
}