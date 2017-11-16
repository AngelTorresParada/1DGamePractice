// TheBest1DAdventureWithAnIProtagonist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include <vector>

#include "Enemy.h"
#include "Bullet.h"
#include "Prize.h"

#define ESC_KEY 27
#define A_KEY 97
#define D_KEY 100
#define K_KEY 107
#define L_KEY 108

#define ENEMY_MAX_CYCLE 30
#define EXTRA_MAX_CYCLE 150
#define MAX_LIVES 5

#define RIGHT 0
#define LEFT 1

const int width = 80;

std::vector<Enemy> enemiesPos;
std::vector<Bullet> bulletsPos;
std::vector<Prize> prizesPos;

int x = width / 2;
int pressedKey = 0;
int enemyCicles = ENEMY_MAX_CYCLE;
int prizeCicles = EXTRA_MAX_CYCLE;
int score = 0;
int lives = MAX_LIVES;

char map[width + 2];
char rain0[width + 1];
char rain1[width + 1];
char rain2[width + 1];
char rain3[width + 1];

bool killGame = false;

void updateCycles();
void buildMap();
void drawMap();
void updateBullet();
void updateEnemy();
void updatePrize();
void checkCollisions();

void buildRain();


void main() {	

	while (!killGame) {

		updateCycles();
		
		buildMap();

		drawMap();

		updateBullet();

		updateEnemy();

		updatePrize();

		checkCollisions();

		//LECTURA DE TECLA
		if (_kbhit()) {
			int pressedKey = _getch();

			switch (pressedKey) {

				case A_KEY:
					if (x != 0) x--;
					break;

				case D_KEY:
					if (x != width - 1) x++;
					break;

				case K_KEY:
					bulletsPos.push_back(Bullet(x - 1, LEFT));
					break;

				case L_KEY:
					bulletsPos.push_back(Bullet(x + 1, RIGHT));
					break;

				case ESC_KEY:
					killGame = true;
					break;
			}

		}
		Sleep(15);
	}
}


void buildMap() {

	for (int i = 0; i < width; i++) {
		map[i] = '0';
	}

	map[x] = 'i';

	for (auto bullet = bulletsPos.begin(); bullet != bulletsPos.end(); ++bullet) {
		if (x > bullet->pos) map[bullet->pos] = '<';
		if (x < bullet->pos) map[bullet->pos] = '>';
	}

	for (auto enemy = enemiesPos.begin(); enemy != enemiesPos.end(); enemy++) {
		map[enemy->pos] = '@';
	}

	for (auto prize = prizesPos.begin(); prize != prizesPos.end(); prize++) {
		map[prize->pos] = '&';
	}

	for (int i = 0; i < width; i++) {
		if (map[i] == '0') map[i] = '_';
	}

	map[width + 1] = '\0';
}


void drawMap() {

	buildRain();

	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("          %s\n", rain0);
	printf("          %s\n", rain1);
	printf("          %s\n", rain2);
	printf("          %s\n", rain3);
	printf("          %s", map);
	printf("   SCORE: %3d\n", score);
	printf("Lives: %d", lives);
	printf("\r");
}


void updateCycles() {

	//CICLOS DE ELEMENTOS SPAWNEABLES

	enemyCicles--;

	prizeCicles--;
}


void updateBullet() {

	//LOGICA DE LA BALA
	for (auto bullet = bulletsPos.begin(); bullet != bulletsPos.end(); bullet++) {
		bullet->update();

		if (bullet->isOutOfField(width)) {
			bulletsPos.erase(bullet);
			return;
		}
	}

}


void updateEnemy() {

	//LOGICA DEL ENEMIGO

	for (auto enemy = enemiesPos.begin(); enemy != enemiesPos.end(); ++enemy) {
		enemy->update();

		if (enemy->isPlayerAttacked(x)) {
			lives--;
			enemiesPos.erase(enemy);
			if (lives <= 0) {
				killGame = true;
				return;
			}
			break;
		}
	}


	if (enemyCicles == 0) {
		int a = rand() % 2;
		Enemy enemy(((a == LEFT) ? width - 1 : 0), a);
		enemiesPos.push_back(enemy);
		enemyCicles = ENEMY_MAX_CYCLE;
	}

}


void checkCollisions() {

	//INTERACCION BALA-ENEMIGO
	for (auto enemy = enemiesPos.begin(); enemy != enemiesPos.end(); enemy++) {
		for (auto bullet = bulletsPos.begin(); bullet != bulletsPos.end(); bullet++) {
			if (enemy->checkBulletCollisions(*bullet)) {
				enemiesPos.erase(enemy);
				bulletsPos.erase(bullet);
				score += 5;
				return;
			}
		}
	}


}


void updatePrize() {

	//LOGICA DEL PREMIO
	if (prizeCicles == 0) {
		prizesPos.push_back(rand() % width);
		prizeCicles = EXTRA_MAX_CYCLE;
	}

	for (auto prize = prizesPos.begin(); prize != prizesPos.end(); prize++) {
		if (prize->isPrizeObtained(x)) {
			score += 100;
			prizesPos.erase(prize);
			break;
		}
	}

	for (auto prize = prizesPos.begin(); prize != prizesPos.end(); prize++) {
		for (auto bullet = bulletsPos.begin(); bullet != bulletsPos.end(); ) {
			if (prize->checkBulletCollisions(*bullet)) {
				bulletsPos.erase(bullet);
				prizesPos.erase(prize);
				return;
			}
			else {
				bullet++;
			}
		}
	}

}


void buildRain() {

	int chance;
	if (rain0 != nullptr) {
		if (rain1 != nullptr) {
			if (rain2 != nullptr) {
				for (int i = 0; i <= width; i++) {
					rain3[i] = rain2[i];
				}
			}
			for (int i = 0; i <= width; i++) {
				rain2[i] = rain1[i];
			}
		}
		for (int i = 0; i <= width; i++) {
			rain1[i] = rain0[i];
		}
	}

	for (int i = 0; i < width; i++) {
		chance = rand();
		if (chance % 10 == 0) rain0[i] = '|';
		else rain0[i] = ' ';
	}
	rain0[width] = '\0';
}

