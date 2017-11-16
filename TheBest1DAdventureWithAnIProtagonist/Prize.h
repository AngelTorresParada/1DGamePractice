#pragma once

#include "Bullet.h"

class Prize {

public:
	static int spawnCycle;

	int pos;

	Prize(int);
	~Prize();

	bool checkBulletCollisions(const Bullet &);

	bool isPrizeObtained(const int);
};
