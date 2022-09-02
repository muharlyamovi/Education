//#include "main.h"
//#include "menu.h"

#define DIRUP_1     1
#define DIRDOWN_1   2
#define DIRLEFT_1   3
#define DIRRIGHT_1  4

#define DIRUP_2     5
#define DIRDOWN_2   6
#define DIRLEFT_2   7
#define DIRRIGHT_2  8

void updateDirection();
void moveCar();
void updateDisplay();
void setGameSpeed();
void updateGame();
void drawRoad();
void enemysDraw();
void checkDuplicate();
void detectCrash();
void gameOver();
void restartGame();
void splashScreen();
void waitForPress();
void rand_pos();

uint8_t randomPosX();
uint8_t randomPosY();
