/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "object.h"

float object::r() const
{
	// V1 - Incorrect
	glm::vec3 r = (glm::vec3(mod->max) * tform.scale);
	return glm::length(r);

	// V2 - Not yet baked into .dat by model processor
	// Average scale - wish to cache this
	float avgs = glm::dot(tform.scale, glm::vec3(1)) / 3.f;
	return mod->r * avgs;
}

object::object()
{
}

object::~object()
{
}

void object::load()
{
	if (mod && !mod->loaded) mod->load();
	if (tex && !tex->loaded) tex->load();
}

void object::unload()
{
	if (mod && mod->loaded) mod->unload();
	if (tex && tex->loaded) tex->unload();
}

void object::render()
{
	tform.upload();
	tex->bind();
	mod->render();
}

template<>
bool object::collides<SPHERE, SPHERE>(const object& b) const
{
	// If dist^2 less than sum of radii squared, then colliding
	glm::vec3 diff = tform.loc - b.tform.loc;

	float rab = r() + b.r();
	
	return (glm::dot(diff, diff) < rab*rab);
}

inline bool testSepAxis(const glm::vec3 & L, const object& a, const object& b)
{
	const glm::vec3& ca = a.tform.loc;
	const glm::vec3& cb = b.tform.loc;

	const glm::vec3& ra = a.tform.R * (glm::sign(L * a.tform.R) * a.mod->max * a.tform.scale);
	const glm::vec3& rb = b.tform.R * (glm::sign(L * b.tform.R) * b.mod->max * b.tform.scale);

	return abs(glm::dot(L, ca - cb)) > abs(glm::dot(L, ra)) + abs(glm::dot(L, rb));
}

template<>
bool object::collides<OBB, OBB>(const object& b) const
{
	// Is a way to derive axes?
	for (int i = 0; i < 3; i++)
	{
		// Axes of a
		if (testSepAxis(tform.R[i], *this, b)) return false;

		// Axes of b
		if (testSepAxis(b.tform.R[i], *this, b)) return false;

		// Axes of b cross with axes of b
		for (int j = 0; j < 3; j++)
		{
			glm::vec3 c = cross(tform.R[i], b.tform.R[j]);
			
			// Don't cross parallel axes
			float m = glm::length(c);
			if (m != 0)	
				if (testSepAxis(c/m, *this, b)) return false;
		}
	}

	return true;
}

template<>
bool object::collides<OBB, SPHERE>(const object& b) const {
	// Nearest point on box to sphere
	glm::vec3 e = mod->max * tform.scale;	// half-width
	glm::vec3 p = tform.loc + tform.R * glm::clamp((b.tform.loc - tform.loc) * tform.R, -e, e);
	
	// Dist from point to sphere
	float d = glm::distance(p, b.tform.loc);

	// If less than sphere radius, collision
	return (d < b.r());
}