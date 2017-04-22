/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "object.h"

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
	tform.render();
	tex->use();
	mod->render();
}

// Collisions
inline float max(glm::vec3 v) {
	float max = v.x;
	if (v.y > max) max = v.y;
	if (v.z > max) max = v.z;
	return max;
}

inline glm::vec3 object::s() const
{
	return mod->max * tform.scale;
}

inline float object::r() const
{
	return max(s());
}

inline float object::r2() const
{
	float r = this->r();
	return r*r;
}

template<>
bool object::collides<AABB>(const object& b) const
{
	glm::vec3 diff = glm::abs(b.tform.loc - tform.loc);
	glm::vec3 size = s() + b.s();

	if (diff.x < size.x) return true;
	if (diff.y < size.y) return true;
	if (diff.z < size.z) return true;

	return false;
}

template<>
bool object::collides<SPHERE>(const object& b) const
{	
	glm::vec3 diff = glm::abs(b.tform.loc - tform.loc);
	float dist2 = glm::dot(diff, diff);

	return (dist2 < r2() + b.r2());
}

inline glm::vec3 rOBB(const object& o, const glm::vec3& L)
{
	return o.tform.R * (glm::sign(L * o.tform.R) * o.mod->max);
}

inline bool testSepAxis(const glm::vec3 & L, const object& a, const object& b)
{
	const glm::vec3& ca = a.tform.loc;
	const glm::vec3& cb = a.tform.loc;

	const glm::vec3& ra = rOBB(a, L);
	const glm::vec3& rb = rOBB(b, L);

	return abs(glm::dot(L, ca - cb)) > abs(glm::dot(L, ra)) + abs(glm::dot(L, rb));
}

template<>
bool object::collides<OBB>(const object& b) const
{
	glm::vec3 L;
	for (int i = 0; i < 3; i++)
	{
		L = tform.R[i];
		if (testSepAxis(L, *this, b)) return false;

		L = b.tform.R[i];
		if (testSepAxis(L, *this, b)) return false;

		for (int j = 0; j < 3; j++)
		{
			glm::vec3 c = cross(tform.R[i], b.tform.R[j]);
			float m = glm::length(c);
			if (m == 0) continue;

			L = c / m;

			if (testSepAxis(L, *this, b)) return false;
		}
	}

	return true;
}