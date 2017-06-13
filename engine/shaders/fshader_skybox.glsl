// Proto Engine : free open-source educational prototype game engine for prototyping simple games.
// Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
// GNU General Public License <http://www.gnu.org/licenses/>.

#version 430

uniform samplerCube myCubemap;

in vec3 texdir;

out vec4 fragColor;

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
	fragColor = texture(myCubemap, texdir);

	float dist = 1000;
	float ambient = 0;
	//fog(dist, ambient);
}