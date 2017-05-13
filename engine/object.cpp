/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "object.h"
#include "engine.h"

object::object() { }

object::~object() { }

bool object::loaded()
{
	return (mod.loaded && tex.loaded);
}

bool object::load()
{
	if (!mod.load()) return false;
	if (!tex.load()) return false;
	return true;
}

void object::update()
{
	script();
	tform.physicsupdate();
	//tform.derivematrix();
}

void object::script()
{
}

void object::render()
{
	glUniformMatrix4fv(3, 1, GL_FALSE, &(glm::translate(tform.loc) * glm::mat4(tform.R) * glm::scale(tform.scale))[0][0]);
	glUniformMatrix3fv(4, 1, GL_FALSE, &(tform.R * glm::mat3(glm::scale(1.0f / tform.scale)))[0][0]);
	glBindTexture(GL_TEXTURE_2D, tex.id);
	glBindVertexArray(mod.vao);
	glDrawArrays(GL_TRIANGLES, 0, mod.nverts);
}

template<> bool object::collides<SPHERE, SPHERE>(const object& b) const
{
	// Collider radius - cache me 
	float as = glm::dot(tform.scale, glm::vec3(1)) / 3.f;
	float ra = mod.r * as;
	float bs = glm::dot(b.tform.scale, glm::vec3(1)) / 3.f;
	float rb = b.mod.r * bs;
	
	// If dist^2 less than sum of radii squared, then colliding
	float rab = ra + rb;
	glm::vec3 diff = tform.loc - b.tform.loc;
	return (glm::dot(diff, diff) < rab*rab);
}

// Collision if dist from sphere to nearest point on box < sphere radius
template<> bool object::collides<BOX, SPHERE>(const object& b) const {
	// Cache these: box half-width and sphere collider radius
	float bs = glm::dot(b.tform.scale, glm::vec3(1)) / 3.f;
	float rb = b.mod.r * bs;
	glm::vec3 e = mod.max * tform.scale;
	
	glm::vec3 p = tform.loc + tform.R * glm::clamp((b.tform.loc - tform.loc) * tform.R, -e, e);
	float d = glm::distance(p, b.tform.loc);
	return (d < rb);
}

// Return true if separated
inline bool testSepAxis(const glm::vec3 & L, const object& a, const object& b)
{
	// Watch for infinite or 0 vectors
	if (glm::length(L) != 1.0f) return false;

	// Collider half-width - cache me 
	glm::vec3 ea = a.mod.max * a.tform.scale;
	glm::vec3 eb = b.mod.max * b.tform.scale;

	// Radial vectors (corner vector that is most aligned along L)
	glm::vec3 ra = a.tform.R * (glm::sign(L * a.tform.R) * ea);
	glm::vec3 rb = b.tform.R * (glm::sign(L * b.tform.R) * eb);

	// If projected distance greater than sum of projected sizes, colliders are separated
	return abs(glm::dot(L, a.tform.loc - b.tform.loc)) > abs(glm::dot(L, ra)) + abs(glm::dot(L, rb));
}

// Test axes of a & b, and a X b. Is there a way to derive best axis? This tight-bound collision test is computationally slow because naive algorithm is brute force.
template<> bool object::collides<BOX, BOX>(const object& b) const
{
	for (int i = 0; i < 3; i++) {
		if (testSepAxis(tform.R[i], *this, b)) return false;
		if (testSepAxis(b.tform.R[i], *this, b)) return false;
		for (int j = 0; j < 3; j++)
			if (testSepAxis(glm::normalize(glm::cross(tform.R[i], b.tform.R[j])), *this, b)) return false;
	}
	return true;
}