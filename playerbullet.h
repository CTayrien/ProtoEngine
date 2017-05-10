#pragma once
#include "object.h"
class playerbullet :
	public object
{
public:
	bool isactive = false;

	playerbullet();
	~playerbullet();

	void script() override;
};

