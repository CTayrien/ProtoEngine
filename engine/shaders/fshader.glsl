// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

#version 430

out vec4 fragColor;

layout (location = 5) uniform vec3 lightLoc;
layout (location = 6) uniform vec3 cameraLoc;

in vec3 worldLoc;
in vec2 uv;
in vec3 worldNorm;

uniform sampler2D myTexture;

layout (location = 7) uniform vec4 material;

void main()
{
	// Frag to Light, Frag to Camera/Eye, Halfway, Normal
	vec3 L = normalize( lightLoc - worldLoc );
	vec3 V = normalize( cameraLoc - worldLoc );
	vec3 H = normalize( L + V );
	vec3 N = normalize( worldNorm );
	
	// Material
	float amb = material[0];
	float dif = material[1] * max(dot(L, N), 0);
	float spec = material[2] * pow(max(dot(H, N), 0), material[3]);
	
	float bright = amb + dif + spec;
	// could easily scale those by distance, and have multiple lights.
	
	vec4 texColor = texture(myTexture, uv);
	fragColor = vec4(bright * texColor.rgb, texColor.a);
}