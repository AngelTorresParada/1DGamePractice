// TheBest1DAdventureWithAnIProtagonist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "windows.h"

#define ESC_KEY 27
#define A_KEY 97
#define D_KEY 100
#define K_KEY 107
#define L_KEY 108

#define ENEMY_MAX_CYCLE 30
#define EXTRA_MAX_CYCLE 150


void main() {	

	const int width = 100;

	int x = 0;
	int bulletPos = x;
	int enemyPos = -1;
	int extraPos = -1;
	int pressedKey = 0;
	int enemyCicles = ENEMY_MAX_CYCLE;
	int enemyAppearance = rand() % 2;
	int extraAppearance = rand() % width;
	int score = 0;

	bool killGame = false;

	printf("\n\n\n\n\n\n\n\n\n");

	while (!killGame) {
		
		//CICLO DEL ENEMIGO
		if (enemyPos == -1) {
			enemyCicles--;
		}

		//PINTADO
		for (int i = 0; i < width; i++) {
			if (i == x) {
				printf("i");
			}
			else {
				if (i == bulletPos) {
					if (x > bulletPos) printf("<");
					else {
						if (x < bulletPos) printf(">");
					}
				}
				else {
					if (i == enemyPos) {
						printf("@");
					}
					else if (i == extraPos) {
						printf("&");
					}
					else printf("_");
				}
			}
		}

		printf("   SCORE: %3d", score);
		printf("\r");


		//LOGICA DEL ENEMIGO
		if (enemyCicles == 0) {
			if (enemyPos == -1) {
				enemyAppearance = rand() % 2;
				if (enemyAppearance) enemyPos = width - 1;
				else enemyPos = 0;
			}
			if (enemyPos < 0 || enemyPos > width - 1) {
				enemyPos = -1;
				enemyCicles = ENEMY_MAX_CYCLE;
			}
			else {
				if (enemyAppearance) enemyPos--;
				else enemyPos++;

				if (enemyPos == x) killGame = true;
			}
		}


		//LOGICA DEL PREMIO


		//LOGICA DE LA BALA
		if (x > bulletPos) bulletPos--;
		else {
			if (x < bulletPos) bulletPos++;
		}

		if (bulletPos < 0 || bulletPos >= width - 1) bulletPos = x;


		//INTERACCION BALA-ENEMIGO
		if (bulletPos == enemyPos || (bulletPos < x && bulletPos + 1 == enemyPos) || (bulletPos > x && bulletPos - 1 == enemyPos)) {
			enemyPos = -1;
			enemyCicles = ENEMY_MAX_CYCLE;
			bulletPos = x;
			score += 5;
		}


		//LECTURA DE TECLA
		if (_kbhit()) {
			int pressedKey = _getch();

			switch (pressedKey) {

				case A_KEY:
					if (x != 0) {
						x--;
						bulletPos--;
					}
					break;

				case D_KEY:
					if (x != width - 1)
					{
						x++;
						bulletPos++;
					}
					break;

				case K_KEY:
					if (x != 0 && bulletPos == x) bulletPos--;
					break;

				case L_KEY:
					if (x != width - 1 && bulletPos == x) bulletPos++;
					break;

				case ESC_KEY:
					killGame = true;
					break;
			}

		}
		Sleep(30);
	}
}

