#include "menu.h"

uint8_t BTNPressed = 0;
uint8_t cursorY = 0;

void MENU_UPDATE()
{
	BTN();
    if (cursorY > 7 && cursorY != 255) cursorY = 7;
    if (cursorY == 0 || cursorY == 255) cursorY = 0;

	ssd1306_Fill(Black);

	ssd1306_SetCursor(30, 0);
   	ssd1306_WriteString("Game", Font_6x8, White);
   	ssd1306_SetCursor(30, 8);
   	ssd1306_WriteString("Menu_2", Font_6x8, White);
   	ssd1306_SetCursor(30, 16);
  	ssd1306_WriteString("Menu_3", Font_6x8, White);
   	ssd1306_SetCursor(30, 24);
   	ssd1306_WriteString("Menu_4", Font_6x8, White);
   	ssd1306_SetCursor(30, 32);
   	ssd1306_WriteString("Menu_5", Font_6x8, White);
   	ssd1306_SetCursor(30, 40);
   	ssd1306_WriteString("Menu_6", Font_6x8, White);
   	ssd1306_SetCursor(30, 48);
   	ssd1306_WriteString("Menu_7", Font_6x8, White);
   	ssd1306_SetCursor(30, 56);
   	ssd1306_WriteString("Menu_8", Font_6x8, White);

	ssd1306_SetCursor(10, cursorY * 8 );
	ssd1306_WriteString("->", Font_7x10, White);

    char str[20];
    itoa(cursorY,str,10);
	ssd1306_SetCursor(110, 4);
	ssd1306_WriteString(str, Font_7x10, White);

	ssd1306_UpdateScreen();
}

void BTN()
{
	updateDir();

	switch (BTNPressed)
	{
	case BTNUP :
		cursorY -= 1;
		BTNPressed = 0;
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		Delay(100);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
    break;
	case BTNDOWN :
		cursorY += 1;
		BTNPressed = 0;
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		Delay(100);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
    break;
	case BTNRIGHT :
		func();
		BTNPressed = 0;
	break;
	/*case BTNLEFT :
    	BTNPressed = 0;
    	flag_menu = 0;
    	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	break;
*/
	}
}

void func(void) {
	ssd1306_Fill(Black);
	switch (cursorY)
	{
	case 0:
		//ssd1306_SetCursor(30, 0);
		//ssd1306_WriteString("Prog_1", Font_6x8, White);
		splashScreen(); //draw_vin
	   	flag_menu = 1;
		//BTN();
	break;
	case 1:
		flag_menu = 2;
	break;
	case 2:
		ssd1306_SetCursor(30, 0);
	   	ssd1306_WriteString("Prog_3", Font_6x8, White);
	break;
	case 3:
		ssd1306_SetCursor(30, 0);
	   	ssd1306_WriteString("Prog_4", Font_6x8, White);
	break;
	case 4:
		ssd1306_SetCursor(30, 0);
	   	ssd1306_WriteString("Prog_5", Font_6x8, White);
	break;
	case 5:
		ssd1306_SetCursor(30, 0);
	   	ssd1306_WriteString("Prog_6", Font_6x8, White);
	break;
	case 6:
		ssd1306_SetCursor(30, 0);
	   	ssd1306_WriteString("Prog_7", Font_6x8, White);
	break;
	case 7:
		ssd1306_SetCursor(30, 0);
	   	ssd1306_WriteString("Prog_8", Font_6x8, White);
	break;
	case 8:
		ssd1306_SetCursor(30, 0);
	   	ssd1306_WriteString("Prog_9", Font_6x8, White);
	break;
	}

	ssd1306_UpdateScreen();

	/*while (1) {
	  BTN();
    if (BTNPressed == BTNLEFT)
    	{
    	BTNPressed = 0;
    	return;
    	}
  }
  */
}

void menu1(void){}
void menu2(void){
	ssd1306_Fill(Black);
	ssd1306_SetCursor(30, 0);
   	ssd1306_WriteString("Prog_2", Font_6x8, White);
    ssd1306_SetCursor(15, 50);
    ssd1306_WriteString("Press key Left OUT", Font_6x8, White);
   	ssd1306_UpdateScreen();
    BTN();
    if (BTNPressed == BTNLEFT)
    	{
    	BTNPressed = 0;
    	flag_menu = 0;
    	}
}
void menu3(void){}
void menu4(void){}

void updateDir(){
	if((GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_11)) == 0)	BTNPressed = BTNUP;
	if((GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_15)) == 0)	BTNPressed = BTNDOWN;
	if((GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_12)) == 0)	BTNPressed = BTNRIGHT;
	if((GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_10)) == 0)	BTNPressed = BTNLEFT;
}
//---------------------------------------------------------------------------
