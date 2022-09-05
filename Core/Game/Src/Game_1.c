#include "main.h"
#include "Game_1.h"
#include "rng.h"

uint8_t dirPressed = 0;
//uint8_t BUTUP = 0;
//uint8_t BUTDWN = 0;
//uint8_t BUTLFT = 0;
//uint8_t BUTRHT = 0;

uint8_t carPosX = 0;
uint8_t carPosY = 0;
uint8_t lanePosArr[4]={0,16,32,48};
uint8_t carPosYCnt = 0;
uint8_t carYTmp = 0;

uint8_t roadLineX1 = 51;
uint8_t roadLineX2 = 102;
uint8_t roadLineX3 = 153;
uint8_t roadLineX4 = 254;
uint8_t roadLineX5 = 200;

uint8_t drawSpeed = 4;

uint8_t enemy0PosX = 132;
uint8_t enemy0PosY = 0;
uint8_t enemy1PosX = 180;
uint8_t enemy1PosY = 0;
uint8_t enemy2PosX = 230;
uint8_t enemy2PosY = 0;

uint32_t score     = 0;
uint32_t compare   = 0;
uint32_t highScore = 5;
uint8_t  metreCnt  = 0;

uint8_t rnd_positions[10] =  {0, 6, 12, 18, 24, 30, 36, 42, 48, 54};
uint16_t res;

uint8_t element[3] = {0};

uint16_t enemy_start_time;
uint8_t logo = 0;

uint16_t num = 0;
//------------------------------- MOVE CAR ----------------------------------------
void moveCar()
   {
	//updateDirection();
	Delay(33);
    if (carPosYCnt > 48) {
    	carPosYCnt = 48;
    }
    if(carPosYCnt < 4 ) carPosYCnt = 4;

	switch (dirPressed)
	{
	case DIRUP_1 :
		if ((HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)) == 0) carPosYCnt -= 4;
		else dirPressed=0;
    break;
    case  DIRDOWN_1 :
    	if ((HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_15)) == 0) carPosYCnt += 4;
		else dirPressed=0;
    break;
    }
}
//-------------------------------------------UPDATE GAME--------------------------------------------------
void updateGame()
{
	if (logo == 0) {
		splashScreen(); //draw_vin
		logo = 1;
	}
	rand_pos();
	moveCar();
    drawRoad();
    draw_car(carPosX, carPosYCnt);
    if ((millis() - enemy_start_time) > 3000){
     enemysDraw();
     detectCrash();
    }
    metreCnt++;
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
    char str[20];
    itoa(score,str,10);
	ssd1306_SetCursor(100, 5);
	ssd1306_WriteString(str, Font_6x8, White);
    //updateDisplay();
	ssd1306_UpdateScreen();
	ssd1306_Fill(Black);
}
//-------------------------------SET GAME SPEED-----------------------------------------------------------
void setGameSpeed()   // this is to speed the rocks and road to moving faster uping the level
{
	if(drawSpeed<10) {
		drawSpeed=drawSpeed + 1;
	}
}
//------------------------------- DRAW ROAD---------------------------------------------------------------
void drawRoad()
{
	for (uint8_t i=0; i<15; i++) {
		for (uint8_t j=0; j<2; j++) {
			ssd1306_DrawPixel(roadLineX1+i, 32+j, White);
		}
	}
	for (uint8_t i=0; i<15; i++) {
		for (uint8_t j=0; j<2; j++) {
			ssd1306_DrawPixel(roadLineX2+i, 32+j, White);
		}
	}
	for (uint8_t i=0; i<15; i++) {
		for (uint8_t j=0; j<2; j++) {
			ssd1306_DrawPixel(roadLineX3+i, 32+j, White);
		}
	}
	for (uint8_t i=0; i<15; i++) {
		for (uint8_t j=0; j<2; j++) {
			ssd1306_DrawPixel(roadLineX4+i, 32+j, White);
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

}
//-----------------------------------------DRAW enemys ---------------------------------------------------
void enemysDraw()
{
	if(enemy0PosX > 220 && enemy0PosX < 230) {
		element[0] = res;
	}
	if(enemy1PosX > 220 && enemy1PosX < 230) {
		element[1] = res;
	}
	if(enemy2PosX > 220 && enemy2PosX < 230) {
		element[2] = res;
	}

	draw_car(enemy0PosX, rnd_positions[element[0]]);
	draw_car(enemy1PosX, rnd_positions[element[1]]);
	draw_car(enemy2PosX, rnd_positions[element[2]]);

	enemy0PosX=enemy0PosX-drawSpeed;
	enemy1PosX=enemy1PosX-drawSpeed;
	enemy2PosX=enemy2PosX-drawSpeed;
}
// ------------------------------------ DETECT CRASH------------------------------------------------------
void detectCrash()
{
	if((enemy0PosX)<=(carPosX + 20) && (rnd_positions[element[0]] + 7) <= (carPosYCnt + 15) && ((rnd_positions[element[0]] + 7) >= carPosYCnt + 0))  gameOver(); // Crashed nto Traffic 0
    if((enemy1PosX)<=(carPosX + 20) && (rnd_positions[element[1]] + 7) <= (carPosYCnt + 15) && ((rnd_positions[element[1]] + 7) >= carPosYCnt + 0))  gameOver();	// Crashed nto Traffic 1
    if((enemy2PosX)<=(carPosX + 20) && (rnd_positions[element[2]] + 7) <= (carPosYCnt + 15) && ((rnd_positions[element[2]] + 7) >= carPosYCnt + 0))  gameOver(); // Crashed nto Traffic 2
}
// ------------------------------ GAME OVER---------------------------------------------------------------
void gameOver()
{
	LL_GPIO_ResetOutputPin(GPIOB, GPIO_PIN_15);
    LL_GPIO_SetOutputPin(GPIOB, GPIO_PIN_2);
    ssd1306_Fill(Black);
    ssd1306_SetCursor(40, 15);
    ssd1306_WriteString("Game", Font_11x18, White);
    ssd1306_SetCursor(40, 30);
    ssd1306_WriteString("over", Font_11x18, White);
    ssd1306_UpdateScreen();
    Delay(1000);
    LL_GPIO_SetOutputPin(GPIOB, GPIO_PIN_15);
    LL_GPIO_ResetOutputPin(GPIOB, GPIO_PIN_2);
    waitForPress();
    restartGame();
}
// ----------------------------------------- RESTART GAME ------------------------------------------------
 void restartGame()
{
	 if(score>=highScore) highScore=score;

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
//------------------------------------------- SPLASH SCREEN -----------------------------------------------
void splashScreen()
{
	ssd1306_Fill(Black);
	draw_vin(0,0);
	draw_logo(51,0);
	ssd1306_UpdateScreen();
	Delay(1000);
}
//-------------------------Wait for press loop -----------------------------------------------------------
void waitForPress()
{
	uint8_t waiting = 0;  // loop ends when this is true
	ssd1306_UpdateScreen();
	while(waiting == 0)
	{
	    char str[20];
	    itoa(score,str,10);

		ssd1306_Fill(Black);
		ssd1306_SetCursor(15, 5);
		ssd1306_WriteString("Your Score:", Font_6x8, White);
		ssd1306_SetCursor(100, 5);
		ssd1306_WriteString(str, Font_6x8, White);

		if(score>=highScore) {
			ssd1306_SetCursor(15, 20);
			ssd1306_WriteString("New record", Font_6x8, White);
		}

		ssd1306_SetCursor(15, 35);
		ssd1306_WriteString("Press key BTN8", Font_6x8, White);
        ssd1306_SetCursor(15, 50);
        ssd1306_WriteString("Press key Left OUT", Font_6x8, White);
		ssd1306_UpdateScreen();
		if ( (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)) == 0 ) {
			waiting = 1;
			dirPressed=0;
			flag_menu = 0;
		}
		if ( (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)) == 0 ) {
			waiting = 1;
			dirPressed=0;
		    logo = 0;
			//BTN();
		}
	}
}
//--------------------------------------------------------------------------------------------------------
void rand_pos()
{
	num = HAL_RNG_GetRandomNumber(&hrng);
	res = num % 10;
}
