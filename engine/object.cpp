/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "object.h"
#include "engine.h"

object::object() { }

object::object(std::string tag, model mod, texture tex)
{
	this->tag = tag;
	this->mod = mod;
	this->tex = tex;
}

object::~object() { }

bool object::loaded()
{
	return (mod.loaded && tex.loaded);
}

bool object::load()
{
	if (!tex.load()) return false;
	if (!mod.load()) return false;
	e = mod.max * tform.scale;
	r = mod.r * (tform.scale.x + tform.scale.y + tform.scale.z) / 3.f;

	return true;
}

void object::update()
{
	script();
	tform.physicsupdate();
}

void object::script()
{
}

void object::render()
{
	glUniformMatrix4fv(3, 1, GL_FALSE, &(glm::translate(tform.loc) * glm::mat4(tform.R) * glm::scale(tform.scale))[0][0]);
	glUniformMatrix3fv(4, 1, GL_FALSE, &(tform.R * glm::mat3(glm::scale(1.0f / tform.scale)))[0][0]);
	glBindTexture(tex.bindpt, tex.id);
	glBindVertexArray(mod.vao);
	glDrawArrays(GL_TRIANGLES, 0, mod.nverts);
}

template<> bool object::collides<SPHERE, SPHERE>(const object& b) const
{
	// If dist^2 less than sum of radii squared, then colliding
	float rab = r + b.r;
	glm::vec3 diff = tform.loc - b.tform.loc;
	return (glm::dot(diff, diff) < rab*rab);
}

template<> bool object::collides<BOX, SPHERE>(const object& b) const {

	// Collision if dist from sphere to nearest point on box < sphere radius
	// This can be a 4x4 matrix operation... T * clamp(DR, -max, max)
	glm::vec3 p = tform.loc + tform.R * glm::clamp((b.tform.loc - tform.loc) * tform.R, -e, e);
	glm::vec3 Dp = b.tform.loc - p;
	return (glm::dot(Dp,Dp) < b.r * b.r);
}

// Return true if separated
inline bool testSepAxis(const glm::vec3 & L, const object& a, const object& b)
{
	// Watch for infinite or 0 vectors
	if (glm::length(L) != 1.0f) return false;

	// Could these be 4x4 matrix ops?
	// Radial vectors (corner vector that is most aligned along L)
	glm::vec3 ra = a.tform.R * a.e * glm::sign(L * a.tform.R);
	glm::vec3 rb = b.tform.R * b.e * glm::sign(L * b.tform.R);

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
			if (testSepAxis(transform::norm(glm::cross(tform.R[i], b.tform.R[j])), *this, b)) return false;
	}
	return true;
}