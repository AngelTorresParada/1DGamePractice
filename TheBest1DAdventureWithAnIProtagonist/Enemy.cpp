#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(int _pos, int _dir) {
	pos = _pos;
	dir = _dir;
}


Enemy::~Enemy() {

}


void Enemy::update() {
	if (dir == LEFT) pos--;
	if (dir == RIGHT) pos++;
}


bool Enemy::checkBulletCollisions(const Bullet &_bullet) {
	return (pos == _bullet.pos || (_bullet.dir == LEFT && _bullet.pos == pos - 1) || (_bullet.dir == RIGHT && _bullet.pos == pos + 1));
}


bool Enemy::isPlayerAttacked(const int _pos) {
	return (pos == _pos);
}