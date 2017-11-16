#include "stdafx.h"
#include "Prize.h"

Prize::Prize(int _pos) {
	pos = _pos;
}


Prize::~Prize() {

}


bool Prize::checkBulletCollisions(const Bullet &_bullet) {
	return (pos == _bullet.pos);
}


bool Prize::isPrizeObtained(const int _pos) {
	return (pos == _pos);
}