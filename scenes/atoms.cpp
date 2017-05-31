/* Atoms: free open-source prototype simulation of atoms forming molecules.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "atoms.h"
#include "engine.h"

class particle : public object {
public:
	enum type{proton, electron, nuetron} t;
	float q;
	float G = 1.f;
	float C = 100.f;

	particle(type t) {
		this->t = t;
		if (t == proton) {
			mtl.rgba = { 1,0,0,1 };
			q = 1;
			tform.mass = 1.f;
		}
		if (t == electron) {
			mtl.rgba = { 0,1,0,1 };
			q = -1;
			tform.mass = .05f;
		}
		if (t == nuetron) {
			mtl.rgba = { 1, 1, 0, 1 };
			q = 0;
			tform.mass = 1.04f;
		}
	}

	void nuetralize(particle *o) {
		if (q * o->q < 0) {
			garbage = true;
			o->garbage = true;

			engine::scene.spawn(new particle(particle::nuetron));
			engine::scene.back()->tform.loc = (tform.loc + o->tform.loc) / 2.f;
			engine::scene.back()->tform.vel = (tform.vel + o->tform.vel) / 2.f;
		}
	}

	void script() override{
		for (size_t i = 2; i < engine::scene.nobjs; i++) {
			particle *o = (particle*)engine::scene.objects[i];
			if (o == this) continue;
			if (garbage || o->garbage) continue;
		
			glm::vec3 d = tform.loc - o->tform.loc;
			float dist = glm::length(d);
			glm::vec3 dir = transform::norm(d);

			if (collides<SPHERE, SPHERE>(*o)) {
				// Nuetralize
				float ke = glm::length(o->tform.vel - tform.vel);
				if (ke < 1) nuetralize(o);
				
				// Bounce
				float rv = glm::dot(dir, o->tform.vel - tform.vel);
				if (rv < 0) {
					tform.vel += (dir * rv);
					o->tform.vel -= (dir * rv);

				}

				// Resurface
				glm::vec3 c = (tform.loc + o->tform.loc) / 2.f;
				tform.loc = c + dir;
				o->tform.loc = c - dir;
			}

			// G & E
			if (dist > 2) {
				tform.force -= dir * G * tform.mass * o->tform.mass / (dist*dist);
				tform.force += dir * C * q * o->q / (dist*dist);
			}
		}
	}
};

#include <ctime>
void atoms()
{
	srand(time(0));
	
	for (size_t i = 0; i < 200; i++) 
	{
		particle::type t = i % 2 ? particle::proton : particle::electron;

		glm::vec3 l;
		l.x = (float)rand() / (float)RAND_MAX * 20 - 10;
		l.y = (float)rand() / (float)RAND_MAX * 20 - 10;
		l.z = (float)rand() / (float)RAND_MAX * 20 - 10;

		engine::scene.spawn(new particle(t));
		engine::scene.back()->tform.loc = l;
	}
}