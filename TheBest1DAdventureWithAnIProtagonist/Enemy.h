#pragma once

#include "Bullet.h"

#define RIGHT 0
#define LEFT 1

class Enemy{

	public:
		static int spawnCycle;

		int pos;
		int dir;

		Enemy(int, int);
		~Enemy();

		void update();

		bool checkBulletCollisions(const Bullet &);

		bool isPlayerAttacked(const int);
};