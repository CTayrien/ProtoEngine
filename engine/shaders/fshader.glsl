// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

#version 430

// Uniforms
layout (location = 6) uniform vec3 camloc;

layout (location = 7) uniform vec4 mtl[2];
uniform sampler2D tex2D;

// Varyings (world coordinates)
in vec3 loc;
in vec2 uv;
in vec3 norm;

// Out
out vec4 fragColor;

// Fog
void fog(float dist, float ambient)
{
	vec3 fogcolor = {.1, .3, .5};
	float atten = .01;
	float fogfactor = clamp( exp(-dist * atten), 0, 1);
	
	vec3 surfcolor = fragColor.rgb;
	vec3 mixcolor = mix(fogcolor, surfcolor, fogfactor);
	vec3 darkcolor = min( surfcolor, mixcolor );

	fragColor.rgb = mix(darkcolor, mixcolor, ambient);
}

void main()
{
	// Scene const (ambient light rgb brightness)
	vec3 ambclr = vec3(1, 1, 1) * mtl[0][0];
	
	// Light const (direct light rgb brightness, could be per light)
	vec3 litloc = normalize(vec3(1, 1, 1)) * 23481;	//23481 earth radii = 1 astronomical unit
	vec3 dirclr = vec3(1, 1, 1);				//could be scaled by dist

	// Texturing
	vec4 texel = texture(tex2D, uv); 

	// Lighting (Diffuse & Specular via Phong-Blinn)
	vec3 L = normalize( litloc - loc );		// Fragment to light
	vec3 V = normalize( camloc - loc );		// Fragment to camera
	vec3 H = normalize( L + V );			// Halfway vector
	vec3 N = normalize( norm );				// Fragment normal
	
	float dif = mtl[0][1] * max(dot(L, N), 0);
	float spec = (mtl[0][2]) * pow(max(dot(H, N), 0), mtl[0][3]);
	
	// Incoming surface light color = Ambient + Diffuse + Specular
	vec3 litclr = ambclr + dirclr * (dif + spec);
	
	// Color
	fragColor = vec4(litclr, 1) * texel * mtl[1];

	float dist = length( camloc - loc );
	float ambient = mtl[0][0];
	fog(dist, ambient);
}