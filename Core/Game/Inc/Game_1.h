//#include "main.h"
//#include "menu.h"

#define DIRUP     1
#define DIRDOWN   2
#define DIRLEFT   3
#define DIRRIGHT  4

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
