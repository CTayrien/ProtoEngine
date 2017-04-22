// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

#version 430

layout (location = 5) uniform vec3 lightLoc;
layout (location = 6) uniform vec3 camLoc;
layout (location = 7) uniform vec4 material;

uniform sampler2D tex2D;

// World space
in vec3 loc;
in vec2 uv;
in vec3 norm;

out vec4 fragColor;

void main()
{
	// Texturing
	vec4 texel = texture(tex2D, uv);

	// Phong-Blinn Lighting
	vec3 L = normalize( lightLoc - loc);	// Fragment to light
	vec3 V = normalize( camLoc - loc);		// Fragment to camera
	vec3 H = normalize( L + V );			// Halfway vector
	vec3 N = normalize( norm );				// Fragment normal
	
	float amb = material[0];
	float dif = material[1] * max(dot(L, N), 0);
	float spec = material[2] * pow(max(dot(H, N), 0), material[3]);
	float light = amb + dif + spec;
	
	// Tex * Light
	vec3 color = light * texel.rgb;
	float alpha = texel.a;

	// Out to color buffer
	fragColor = vec4(color, texel.a);
}