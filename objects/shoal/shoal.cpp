#include "shoal.h"
#include "engine.h"

shoal::shoal()
{
}

shoal::~shoal()
{
}

void shoal::script()
{
	// press a button to make the shoal flash the shark
	if (engine::input.down[input_e]) {
		mystate = state::flash;
	}
	else {
		mystate = state::flee;
	}

	// advance or decrease flasht
	float d = (mystate == state::flash) ? 1 : -1;
	flasht += d * engine::timer.dt / flashp;
	flasht = glm::clamp(flasht, 0.f, 1.f);
}

void shoal::render()
{
	// shoal itself should not be visible ... but it is?
}

fish::fish()
{
	mod = model({"engine/models/box.dat"});
	mtl.adsa = { 0, 0, 1, 256 };
	mtl.rgba = { 1, 1, 1, 1 };
	tform.scale = { 2, 1, .2 };
}

fish::~fish()
{
}

void fish::flash(glm::vec3 lightdir, glm::vec3 sharkdir)
{
	glm::vec3 halfway = glm::normalize(lightdir + sharkdir);
	
	transform flashtform;
	flashtform.setforwardandroll(halfway, 0);

	// slerp (broken?) or lerp
	float t = theshoal->flasht;
	glm::mat3 qa = theshoal->tform.R;
	glm::mat3 qb = flashtform.R;
	
	//tform.slerp(qa, qb, t);
	tform.R = glm::mix(qa, qb, t);
}

void fish::script()
{
	// Flash
	glm::vec3 sharkdir = glm::normalize(theshoal->theshark->tform.loc - tform.loc);
	flash(theshoal->lightdir, sharkdir);
	if (theshoal->mystate == theshoal->flash) return;

	//need seekdir?
	// Flee:
	glm::vec3 perp = glm::normalize(glm::cross(sharkdir, { 0,1,0 }));
	float sharkdist = glm::length(theshoal->theshark->tform.loc - tform.loc);
	tform.vel = (sharkdist < 5) ? sharkdir : perp;
	tform.vel *= 5;
	//tform.setforwardandroll(tform.vel, 0);

	// Flocking
	// Alignment - velocity & orientation same vs fish, perpendicular & max speed vs shark
	tform.R = theshoal->tform.R;
	tform.vel = theshoal->tform.vel;

	for (auto& fish : theshoal->fishes) {
		if (this == fish) continue;
		float r = 10;
		float dist = glm::distance(tform.loc, fish->tform.loc);
		if (dist == 0) continue;
		glm::vec3 dir = glm::normalize(tform.loc - fish->tform.loc);

		// Cohesion - attract if in range but distant
		if (dist > 20) tform.loc -= dir * .01f;

		// Separation - repel if too close
		if (dist < 20) tform.loc += dir * .01f / dist;
	}
}