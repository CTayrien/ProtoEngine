#pragma once
#include "object.h"
class fish;

class shoal :
	public object
{
public:
	shoal();
	~shoal();

	glm::vec3 lightdir = glm::normalize(glm::vec3(1, 1, 1) * 23481.f);
	glm::vec3 fleedir = { 1, 0, 0 };
	float flasht = 0;
	float flashp = .1f;
	enum state { flee, flash } mystate;
	object* theshark;
	std::vector<fish*> fishes;
	void script() override;
	void render() override;
};

class fish :
	public object {
public:
	fish();
	~fish();

	void flash(glm::vec3 lightdir, glm::vec3 sharkdir);
	shoal* theshoal;
	void script() override;
};