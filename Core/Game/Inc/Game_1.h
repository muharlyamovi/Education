/*
 * game_2.h
 *
 *  Created on: 5 сент. 2022 г.
 *      Author: Muharlyamov
 */

#ifndef GAME_INC_GAME_1_H_
#define GAME_INC_GAME_1_H_

#include "main.h"

#define DIRUP_1     1
#define DIRDOWN_1   2
#define DIRLEFT_1   3
#define DIRRIGHT_1  4

#define DIRUP_2     5
#define DIRDOWN_2   6
#define DIRLEFT_2   7
#define DIRRIGHT_2  8

uint8_t randomPosX();
uint8_t randomPosY();

uint8_t dirPressed;
uint8_t carPosX;
uint8_t carPosY;
uint8_t lanePosArr[4];	// Array to store where each lane is
uint8_t carPosYCnt;
uint8_t carYTmp;
						// Variables for the lines in the road
uint8_t roadLineX1;
uint8_t roadLineX2;
uint8_t roadLineX3;
uint8_t roadLineX4;
uint8_t roadLineX5;

uint8_t drawSpeed;

uint8_t enemy0PosX;
uint8_t enemy0PosY;
uint8_t enemy1PosX;
uint8_t enemy1PosY;
uint8_t enemy2PosX;
uint8_t enemy2PosY;
						// Score counter
uint32_t score;			// This is the score
uint32_t compare;		// This stores the  score at the last level up to compare back to
uint32_t highScore;
uint8_t  metreCnt;

uint8_t rnd_positions[10];
uint16_t res;

uint8_t element[3];

uint16_t enemy_start_time;
uint8_t logo;

uint16_t num;
//extern volatile uint8_t flag_menu;

void moveCar();
void updateGame();
void setGameSpeed();
void drawRoad();
void enemysDraw();
void detectCrash();
void gameOver();
void restartGame();
void splashScreen();
void waitForPress();
void rand_pos();

#endif /* GAME_INC_GAME_1_H_ */
