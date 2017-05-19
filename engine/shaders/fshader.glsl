// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

#version 430

// Uniforms
uniform sampler2D tex2D;

layout (location = 6) uniform vec3 camloc;

// Varyings (world coordinates)
in vec3 loc;
in vec2 uv;
in vec3 norm;

// Out
out vec4 fragColor;

void main()
{
	// Material const (diffuse vs specular, specular alpha)
	vec2 mtrl = vec2(.5, 32);		//strange mtrl
	
	// Scene const (ambient light rgb brightness)
	vec3 ambclr = vec3(1, 1, 1) * .5;
	
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
	
	float dif = mtrl[0] * max(dot(L, N), 0);
	float spec = (1-mtrl[0]) * pow(max(dot(H, N), 0), mtrl[1]);
	
	// Incoming surface light color = Ambient + Diffuse + Specular
	vec3 litclr = ambclr + dirclr * (dif + spec);
	
	// Color
	fragColor = vec4(litclr, 1) * texel;
}