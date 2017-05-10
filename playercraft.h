#pragma once
#include "object.h"
#include "playerbullet.h"

class playercraft :
	public object
{
public:
	playerbullet bulletprefab;//set up in c'tor? 
	
	playerbullet bullets[10];
	int cbullet = 0;
	int nbullets = 10;

	playercraft();
	~playercraft();

	void script() override;
};