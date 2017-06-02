/* Orbits: free open-source prototype simulation of orbiting between earth-moon system.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "orbits.h"
#include "engine.h"

#include <iostream>

object *earth, *moon, *craftptr;
float G = 1;

class craft : public object {
public:
	float dm = .1;		// mass ejection rate per second
	float ev = 1000;	// exit velocity
	float m0 = 1;		// min mass
	float m1 = 2;		// start mass

	craft() {
		tform.mass = m1;
		mtl.rgba = { 0, 1, 0, 1 };
	}

	void grav(object* o) {
		glm::vec3 d = o->tform.loc - tform.loc;
		float dist = glm::length(d);
		glm::vec3 dir = d / dist;

		tform.force += dir * G * tform.mass * o->tform.mass / (dist * dist);
	}

	void script() override {
		// move camera behind & above craft
		if (0 == engine::input.down[input_mouse_left]) {
			engine::cam.tform.loc = tform.loc;
			engine::cam.tform.loc -= 10.f * engine::cam.tform.forward();
			engine::cam.tform.loc += 5.f * engine::cam.tform.up();
		}
		
		// grav craft to earth & moon
		grav(earth);
		grav(moon);

		// Ejecta direction
		glm::vec3 ed;
		if (engine::input.down[input_space]) {
			ed = transform::norm(-engine::cam.tform.forward());
		}
		else if (engine::input.down[input_ctrl]) {
			ed = transform::norm(tform.vel);
		}
		
		// if mass > m0, spacebar adds force and decreases mass const per unit time, ctrl brakes.
		if (ed != glm::vec3() && tform.mass > m0) {
			// Rocket science
			object* fuel = engine::scene.spawn(new object);
			fuel->tform = tform;
			fuel->tform.vel += ed*ev;
			fuel->tform.scale *= .5f;
			fuel->mtl.adsa[3] = .5f;

			// Rocket mass loss
			tform.mass -= dm * engine::timer.dt;
			
			// Ejecta momentum
			glm::vec3 dp = ed * (dm * engine::timer.dt * ev);
			
			// Rocket momentum change
			tform.vel -= dp / tform.mass;
			
			// Fuel gauge
			glm::vec4 red = { 1, 0, 0, 1 };
			glm::vec4 green = { 0, 1, 0, 1 };
			float t = (tform.mass - m0) / (m1 - m0);
			glm::vec4 color = glm::mix(red, green, t);
			mtl.rgba = color;
		}
	}
};

class burnzone : public object {
public:
	burnzone() {
		mod = model({ "engine/models/box.dat" });
		mtl.rgba = { 1, 1, 0, .5 };
	}
	void render() override {
		// Render interior of back side
		glCullFace(GL_FRONT);
		object::render();
		glCullFace(GL_BACK);

		// Render exterior of front side
		object::render();
	}
};

void orbits() 
{
	printf("\nOrbits: free open-source prototype simulation of orbiting between earth-moon system.\nTo achieve transition orbit, burn thrusters in direction of moon in burn zone in earth orbit.\nIn burn zone in moon orbit, fire thrusters toward earth to achieve moon orbit.\nHold spacebar to fire main thrusters in the camera's forward direction. \nTo fire in direction opposite of motion, press ctrl.\n Ship color (gree->red) indicates fuel level. \n10 seconds worth of fuel exists.\nFull fuel tank weighs as much as the rest of the craft.\n\nFlaws:\nobject scales & forces\nDraw distance (far clip plane too aggressive)\nModels are too simple.\nCannot orbit moon because: moon isn't in orbit around earth. \nMatching moon's angular v at its r from earth should counteract earth g\nCamera jitters because craft moves camera\n.");
	engine::cam.isdebug = true;

	// Earth
	earth = engine::scene.spawn(new object);
	earth->tform.mass = 100 * 100 * 100;
	earth->tform.scale *= 100;
	earth->tform.loc.z = 100 * 4;
	earth->mtl.adsa = { 0,1,.5,32 };
	earth->tex = texture({ "objects/planet/earth.png" });

	// Moon
	moon = engine::scene.spawn(new object);
	moon->tform.mass = 10 * 10 * 10;
	moon->tform.scale *= 10;
	moon->tform.loc.z = -100 * 4;
	moon->mtl.adsa = { 0,1,.5,32 };
	moon->tex = texture({ "objects/moon/moon.png" });
	
	// Craft
	craftptr = engine::scene.spawn(new craft);
	craftptr->mtl.adsa = { 0,1,.5,32 };
	craftptr->tform.loc.z = 100 / 2;
	craftptr->tform.vel.x = 100 / 2;

	object *bt0, *bt1;
	bt0 = engine::scene.spawn(new burnzone);
	bt0->tform.loc = earth->tform.loc + glm::vec3{-300,0,0};
	bt0->tform.scale = glm::vec3(10,10,40);

	bt1 = engine::scene.spawn(new burnzone);
	bt1->tform.loc = moon->tform.loc + glm::vec3{ -150,0,0 };
	bt1->tform.scale = glm::vec3(20, 20, 50);
}