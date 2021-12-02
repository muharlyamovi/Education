#include "main.h"
#include "game.h"

// define directions
#define DIRUP     1       // these values is what the "snake" looks at to decide-
#define DIRDOWN   2       // the direction the snake will travel
#define DIRLEFT   3
#define DIRRIGHT  4

uint8_t dirPressed = 0; // value to register direction to move on which pin went high

// booleans store which pin went high
uint8_t BUTUP  = 0;
uint8_t BUTDWN = 0;
uint8_t BUTLFT = 0;
uint8_t BUTRHT = 0;
// vars for the position of the car
uint8_t carPosX = 0;
//uint8_t carPosY[] = {0,16,32,48};  // needs value cahnging the the array
uint8_t carPosY = 0;
uint8_t lanePosArr[]={0,16,32,48};  // array to store where each lane is
uint8_t carPosYCnt = 0;
uint8_t carYTmp = 0;

// variables for the lines in the road
uint8_t roadLineX1 = 51;             // these are predefined at the begining then the lines appear seamless
uint8_t roadLineX2 = 102;
uint8_t roadLineX3 = 153;
uint8_t roadLineX4 = 254;
uint8_t roadLineX5 = 200;

// this is how many pixels the play area moves at a time
uint8_t drawSpeed = 4;

// vars for enemy0
uint8_t enemy0PosX = 132;
uint8_t enemy0PosY = 0;
uint8_t enemy1PosX = 180;
uint8_t enemy1PosY = 0;
uint8_t enemy2PosX = 230;
uint8_t enemy2PosY = 0;

// score counter
uint32_t score     = 0;     // this is the score :/ lol
uint32_t compare   = 0;   // this stores the  score at the last level up to compare back to
uint32_t highScore = 5;
uint8_t  metreCnt  = 0;

uint8_t rnd_positions[10] =  {0, 6, 12, 18, 24, 30, 36, 42, 48, 54};
uint16_t res;
uint8_t element[3] = {0};

uint16_t enemy_start_time;

//-------------------------- UPDATE DIRECTION (player) --------------------------
void updateDirection()
{
	if((GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_15)) == 0)	dirPressed = DIRDOWN;
	if((GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_11)) == 0)	dirPressed = DIRUP;
	//if((GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_10)) == 0)	dirPressed = DIRLEFT;
	//if((GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_12)) == 0)	dirPressed = DIRRIGHT;
}
//------------------------------- MOVE CAR ----------------------------------------
void moveCar()
   {
	updateDirection();
	Delay(33);
    if (carPosYCnt > 48) {
    	carPosYCnt = 48;
    }
    if(carPosYCnt < 5 ) carPosYCnt = 5;

	switch (dirPressed)
	{
	case DIRUP :
		carPosYCnt-=5;

        dirPressed=0;
    break;
    case  DIRDOWN :
        carPosYCnt+=5;

        dirPressed=0;
    break;
    }
}
//------------------------------------ UPDATE DISPLAY------------------------------------------------
void updateDisplay()
{
	//ssd1306_SetCursor(100, 0);
	//ssd1306_WriteString(score, Font_16x26, White);
	ssd1306_UpdateScreen();
	ssd1306_Fill(Black);
}
//-------------------------------------------UPDATE GAME-----------------------------------------
void updateGame()
{
	moveCar();
    drawRoad();
    draw_car(carPosX, carPosYCnt);
    if ((millis() - enemy_start_time) > 3000){
     enemysDraw();
     detectCrash();
    }
    metreCnt++;
    updateDisplay();
    if(metreCnt == 5)// adds a point for every 10 cycles to clock up score
    {
    	metreCnt = 0;
        score++;
    }
    if(score == compare+5) // this calls the get faster function every five points
    {
        compare = score;
        setGameSpeed();
    }
}
//-------------------------------SET GAME SPEED----------------------------
void setGameSpeed()   // this is to speed the rocks and road to moving faster uping the level
{
	if(drawSpeed<10) drawSpeed=drawSpeed++;
}
//------------------------------- DRAW ROAD------------------------------------
void drawRoad()
{
	for (uint8_t i=0; i<15; i++) {
		for (uint8_t j=0; j<2; j++) {
			//ssd1306_DrawPixel(roadLineX1+i, 15+j, White);
			ssd1306_DrawPixel(roadLineX1+i, 32+j, White);
			//ssd1306_DrawPixel(roadLineX1+i, 45+j, White);
		}
	}
	for (uint8_t i=0; i<15; i++) {
		for (uint8_t j=0; j<2; j++) {
			//ssd1306_DrawPixel(roadLineX2+i, 15+j, White);
			ssd1306_DrawPixel(roadLineX2+i, 32+j, White);
			//ssd1306_DrawPixel(roadLineX2+i, 45+j, White);
		}
	}
	for (uint8_t i=0; i<15; i++) {
		for (uint8_t j=0; j<2; j++) {
			//ssd1306_DrawPixel(roadLineX3+i, 15+j, White);
			ssd1306_DrawPixel(roadLineX3+i, 32+j, White);
			//ssd1306_DrawPixel(roadLineX3+i, 45+j, White);
		}
	}
	for (uint8_t i=0; i<15; i++) {
		for (uint8_t j=0; j<2; j++) {
			//ssd1306_DrawPixel(roadLineX4+i, 15+j, White);
			ssd1306_DrawPixel(roadLineX4+i, 32+j, White);
			//ssd1306_DrawPixel(roadLineX4+i, 45+j, White);
		}
	}
	for (uint8_t i=0; i<15; i++) {
		for (uint8_t j=0; j<2; j++) {
			//ssd1306_DrawPixel(roadLineX5+i, 15+j, White);
			ssd1306_DrawPixel(roadLineX5+i, 32+j, White);
			//ssd1306_DrawPixel(roadLineX5+i, 45+j, White);
		}
	}
    roadLineX1=roadLineX1-drawSpeed;
    roadLineX2=roadLineX2-drawSpeed;
    roadLineX3=roadLineX3-drawSpeed;
    roadLineX4=roadLineX4-drawSpeed;
    roadLineX5=roadLineX5-drawSpeed;
    //ssd1306_UpdateScreen();
}
//-----------------------------------------DRAW enemys -------------------------------------------
void enemysDraw()
{
	if(enemy0PosX>220&&enemy0PosX<230) {
		element[0] = res;
	}
	if(enemy1PosX>220&&enemy1PosX<230) {
		element[1] = res;
	}
	if(enemy2PosX>220&&enemy2PosX<230) {
		element[2] = res;
	}

	draw_car(enemy0PosX, rnd_positions[element[0]]);
	draw_car(enemy1PosX, rnd_positions[element[1]]);
	draw_car(enemy2PosX, rnd_positions[element[2]]);

	enemy0PosX=enemy0PosX-drawSpeed;
	enemy1PosX=enemy1PosX-drawSpeed;
	enemy2PosX=enemy2PosX-drawSpeed;
}
// ------------------------------------ DETECT CRASH---------------------------------
void detectCrash()
{
	if((enemy0PosX)<=(carPosX + 20) && (rnd_positions[element[0]] + 7) <= (carPosYCnt + 15) && ((rnd_positions[element[0]] + 7) >= carPosYCnt + 0))  gameOver(); // Crashed nto Traffic 0
    if((enemy1PosX)<=(carPosX + 20) && (rnd_positions[element[1]] + 7) <= (carPosYCnt + 15) && ((rnd_positions[element[1]] + 7) >= carPosYCnt + 0))  gameOver();	// Crashed nto Traffic 1
    if((enemy2PosX)<=(carPosX + 20) && (rnd_positions[element[2]] + 7) <= (carPosYCnt + 15) && ((rnd_positions[element[2]] + 7) >= carPosYCnt + 0))  gameOver(); // Crashed nto Traffic 2
}
// ------------------------------ GAME OVER----------------------------------------------
void gameOver()
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_15);
    GPIO_SetBits(GPIOB, GPIO_Pin_2);
    ssd1306_Fill(Black);
    ssd1306_SetCursor(40, 15);
    ssd1306_WriteString("Game", Font_11x18, White);
    ssd1306_SetCursor(40, 30);
    ssd1306_WriteString("over", Font_11x18, White);
    //draw_end(enemy0PosX, enemy0PosY);
    ssd1306_UpdateScreen();
    Delay(2000);
    GPIO_SetBits(GPIOB, GPIO_Pin_15);
    GPIO_ResetBits(GPIOB, GPIO_Pin_2);
    waitForPress();
    restartGame();
}
// ----------------------------------------- RESTART GAME ------------------------------------------------------------
 void restartGame()
{
//	 if(score>=highScore)   //check to see if score higher than high score
//     {
//     highScore=score;  //single if statment to update high score
//     }
	 score=0;
	 drawSpeed=4;
     metreCnt=0;
     enemy0PosX = 132;
     enemy0PosY = 0;
     enemy1PosX = 200;
     enemy1PosY = 0;
     enemy2PosX = 250;
     enemy2PosY = 0;
     enemy_start_time = millis();
}
//------------------------------------------- SPLASH SCREEN -----------------------------------
void splashScreen()
{
	ssd1306_Fill(Black);
	//draw_logo(enemy0PosX, enemy0PosY);
	draw_vin(0,0);
	draw_logo(51,0);
	ssd1306_UpdateScreen();
	Delay(2000);
}
//-------------------------wait for presss loop -------------------------
void waitForPress()
{
	//splashScreen();
	uint8_t waiting = 0;  // loop ends when this is true
	ssd1306_UpdateScreen();
	while(waiting == 0)
	{
	    char str[20];
	    itoa(highScore,str,10);
	    //ssd1306_Fill(Black);

//	    ssd1306_SetCursor(20, 5);
//	    ssd1306_WriteString(str, Font_7x10, White);
//	    ssd1306_UpdateScreen();

		ssd1306_Fill(Black);
		ssd1306_SetCursor(20, 50);
		ssd1306_WriteString("Press key BTN8", Font_7x10, White);
		ssd1306_SetCursor(20, 10);
		ssd1306_WriteString("Your Score:", Font_7x10, White);
		ssd1306_SetCursor(20, 30);
		ssd1306_WriteString(str, Font_7x10, White);
		ssd1306_UpdateScreen();
		waiting = !(GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_9)); // BTN8
        dirPressed=0;        // reset button press to no direction
	}
}
