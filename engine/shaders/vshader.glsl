// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

// Vertex shader: transform model data to world space (for lighting) and view space

#version 430

// Attributes (model space vertex data)
layout (location = 0) in vec3 modelLoc;
layout (location = 1) in vec2 modelUV;
layout (location = 2) in vec3 modelNorm;

// Uniforms (transformations of object and camera)
layout (location = 3) uniform mat4 modelWorld;
layout (location = 4) uniform mat3 normtform;
layout (location = 5) uniform mat4 worldView;

// Varying (world space vertex and fragment data)
out vec3 loc;
out vec2 uv;
out vec3 norm;
out vec3 normmod;

void main()
{
	// World space
	loc = (modelWorld * vec4(modelLoc, 1)).xyz;
	uv = modelUV;
	norm = normalize(normtform * modelNorm);
	normmod = modelNorm;

	// View space
	gl_Position = worldView * vec4(loc, 1);
}