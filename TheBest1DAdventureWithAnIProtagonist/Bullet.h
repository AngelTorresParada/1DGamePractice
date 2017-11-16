#pragma once

#define RIGHT 0
#define LEFT 1

class Bullet {

public:

	int pos;
	int dir;

	Bullet(int, int);
	~Bullet();

	void update();
	bool isOutOfField(const int);
};
