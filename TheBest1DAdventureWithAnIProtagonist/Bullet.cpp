#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(int _pos, int _dir) {
	pos = _pos;
	dir = _dir;
}


Bullet::~Bullet() {

}


void Bullet::update() {
	if (dir == LEFT) pos--;
	if (dir == RIGHT) pos++;
}


bool Bullet::isOutOfField(const int _width) {
	return (pos < 0 || pos >= (_width - 1));
}