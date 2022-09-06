#include "menu.h"

uint8_t BTNPressed = 0;
uint8_t cursorY = 0;
uint8_t flag_in = 0;
uint8_t flag_up = 0;
uint8_t flag_down = 0;
volatile uint8_t flag_menu = 0;

//---------------------------------------------------------------------------
void MENU_GENERAL()
{
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

	ssd1306_SetCursor(10, (cursorY*8));
	ssd1306_WriteString("->", Font_6x8, White);

    char str[20];
    itoa(cursorY+1,str,10);
	ssd1306_SetCursor(115, 4);
	ssd1306_WriteString(str, Font_6x8, White);

	ssd1306_UpdateScreen();
	BTN();
}
//---------------------------------------------------------------------------
void MENU_SECOND(){
	flag_in = 1;
	flag_up = 1;
	flag_down = 1;
	switch (flag_menu)
		{
		case 1:
			updateGame();
		break;
		case 2:
			ssd1306_Fill(Black);
			ssd1306_SetCursor(30, 0);
		   	ssd1306_WriteString("Prog_2", Font_6x8, White);
			ssd1306_SetCursor(15, 40 );
			ssd1306_WriteString("<-", Font_6x8, White);
		    ssd1306_SetCursor(15, 50);
		    ssd1306_WriteString("Press key Left OUT", Font_6x8, White);
		   	ssd1306_UpdateScreen();
		   	BTN();
		break;
		case 3:
			ssd1306_Fill(Black);
			ssd1306_SetCursor(30, 0);
		   	ssd1306_WriteString("Prog_3", Font_6x8, White);
		    ssd1306_SetCursor(15, 50);
		    ssd1306_WriteString("Press key Left OUT", Font_6x8, White);
		   	ssd1306_UpdateScreen();
		   	BTN();
		break;
		case 4:
			ssd1306_Fill(Black);
			ssd1306_SetCursor(30, 0);
		   	ssd1306_WriteString("Prog_4", Font_6x8, White);
		    ssd1306_SetCursor(15, 50);
		    ssd1306_WriteString("Press key Left OUT", Font_6x8, White);
		   	ssd1306_UpdateScreen();
		   	BTN();
		break;
		case 5:
			ssd1306_Fill(Black);
			ssd1306_SetCursor(30, 0);
		   	ssd1306_WriteString("Prog_5", Font_6x8, White);
		    ssd1306_SetCursor(15, 50);
		    ssd1306_WriteString("Press key Left OUT", Font_6x8, White);
		   	ssd1306_UpdateScreen();
		   	BTN();
		break;
		case 6:
			ssd1306_Fill(Black);
			ssd1306_SetCursor(30, 0);
		   	ssd1306_WriteString("Prog_6", Font_6x8, White);
		    ssd1306_SetCursor(15, 50);
		    ssd1306_WriteString("Press key Left OUT", Font_6x8, White);
		   	ssd1306_UpdateScreen();
		   	BTN();
		break;
		case 7:
			ssd1306_Fill(Black);
			ssd1306_SetCursor(30, 0);
		   	ssd1306_WriteString("Prog_7", Font_6x8, White);
		    ssd1306_SetCursor(15, 50);
		    ssd1306_WriteString("Press key Left OUT", Font_6x8, White);
		   	ssd1306_UpdateScreen();
		   	BTN();
		break;
		case 8:
			ssd1306_Fill(Black);
			ssd1306_SetCursor(30, 0);
		   	ssd1306_WriteString("Prog_8", Font_6x8, White);
		    ssd1306_SetCursor(15, 50);
		    ssd1306_WriteString("Press key Left OUT", Font_6x8, White);
		   	ssd1306_UpdateScreen();
		   	BTN();
		break;
		}
}
//---------------------------------------------------------------------------
void updateDir(){
	if((HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)) == 0)	BTNPressed = DIRUP_1;
	if((HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_15)) == 0)	BTNPressed = DIRDOWN_1;
	if((HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_12)) == 0)	BTNPressed = DIRRIGHT_1;
	if((HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)) == 0)	BTNPressed = DIRLEFT_1;
}
//---------------------------------------------------------------------------
void BTN()
{
	updateDir();
	switch (BTNPressed)
	{
	case DIRUP_1 :
		if (flag_up == 0) {
			LL_GPIO_ResetOutputPin(GPIOB, GPIO_PIN_15);
			Delay(100);
			LL_GPIO_SetOutputPin(GPIOB, GPIO_PIN_15);
			cursorY -= 1;
			BTNPressed = 0;
		}
    break;
	case DIRDOWN_1 :
		if (flag_down == 0) {
			LL_GPIO_ResetOutputPin(GPIOB, GPIO_PIN_15);
			Delay(100);
			LL_GPIO_SetOutputPin(GPIOB, GPIO_PIN_15);
			cursorY += 1;
			BTNPressed = 0;
		}
    break;
	case DIRRIGHT_1 :
		if (flag_in == 0) {
			LL_GPIO_ResetOutputPin(GPIOB, GPIO_PIN_14);
			Delay(100);
			LL_GPIO_SetOutputPin(GPIOB, GPIO_PIN_14);
			flag_menu = cursorY+1;
			BTNPressed = 0;
			MENU_SECOND();
		}
	break;
	case DIRLEFT_1 :
		LL_GPIO_ResetOutputPin(GPIOB, GPIO_PIN_14);
		Delay(100);
		LL_GPIO_SetOutputPin(GPIOB, GPIO_PIN_14);
    	flag_in = 0;
    	flag_up = 0;
    	flag_down = 0;
    	flag_menu = 0;
    	BTNPressed = 0;
	break;
	}
	if (cursorY > 7 && cursorY != 255) cursorY = 7;
  	if (cursorY == 0 || cursorY == 255) cursorY = 0;
}
