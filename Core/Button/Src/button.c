/*
 * button.c
 *
 *  Created on: 7 сент. 2022 г.
 *      Author: Muharlyamov
 */
#include "button.h"
#include "MicroMenu.h"

struct btn_struct button_struct;
struct flag_menu flag_m;

void button_counter (){
	if (button_struct.btn_A == PRESSED || button_struct.btn_A == PRESSED_LONG) button_struct.counters_btn[0]++; //BTN6(PC7)  - BTN A
	else button_struct.counters_btn[0] = IDLE;
	if (button_struct.btn_B == PRESSED || button_struct.btn_B == PRESSED_LONG) button_struct.counters_btn[1]++;	//BTN5(PB12) - BTN B
	else button_struct.counters_btn[1] = IDLE;
	if (button_struct.btn_X == PRESSED || button_struct.btn_X == PRESSED_LONG) button_struct.counters_btn[2]++; //BTN7(PC8)  - BTN X
	else button_struct.counters_btn[2] = IDLE;
	if (button_struct.btn_Y == PRESSED || button_struct.btn_Y == PRESSED_LONG) button_struct.counters_btn[3]++;	//BTN8(PC9)  - BTN Y
	else button_struct.counters_btn[3] = IDLE;

	if (button_struct.btn_D == PRESSED || button_struct.btn_D == PRESSED_LONG) button_struct.counters_btn[4]++;	//BTN1(PA15) - BTN D
	else button_struct.counters_btn[4] = IDLE;
	if (button_struct.btn_R == PRESSED || button_struct.btn_R == PRESSED_LONG) button_struct.counters_btn[5]++;	//BTN4(PC12) - BTN R (NO EXTI)
	else button_struct.counters_btn[5] = IDLE;
	if (button_struct.btn_L == PRESSED || button_struct.btn_L == PRESSED_LONG) button_struct.counters_btn[6]++;	//BTN2(PC10) - BTN L
	else button_struct.counters_btn[6] = IDLE;
	if (button_struct.btn_U == PRESSED || button_struct.btn_U == PRESSED_LONG) button_struct.counters_btn[7]++;	//BTN3(PC11) - BTN U
	else button_struct.counters_btn[7] = IDLE;
}

void button_update() {

		if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_7) == 0 ) {
			if (button_struct.counters_btn[0] > WAIT) button_struct.btn_A = PRESSED_LONG;
			else button_struct.btn_A = PRESSED;
		}
		else button_struct.btn_A = IDLE;

		if (HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12) == 0 ) {
			if (button_struct.counters_btn[1] > WAIT) button_struct.btn_B = PRESSED_LONG;
			else button_struct.btn_B = PRESSED;
		}
		else button_struct.btn_B = IDLE;

		if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_8) == 0 ) {
			if (button_struct.counters_btn[2] > WAIT) button_struct.btn_X = PRESSED_LONG;
			else button_struct.btn_X = PRESSED;
		}
		else button_struct.btn_X = IDLE;

		if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9) == 0 ) {
			if (button_struct.counters_btn[3] > WAIT) button_struct.btn_Y = PRESSED_LONG;
			else button_struct.btn_Y = PRESSED;
		}
		else button_struct.btn_Y = IDLE;

		if (HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_15) == 0 ) {
			if (button_struct.counters_btn[4] > WAIT) button_struct.btn_D = PRESSED_LONG;
			else button_struct.btn_D = PRESSED;
		}
		else button_struct.btn_D = IDLE;

		if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_12) == 0 ) {
			if (button_struct.counters_btn[5] > WAIT) button_struct.btn_R = PRESSED_LONG;
			else button_struct.btn_R = PRESSED;
		}
		else button_struct.btn_R = IDLE;

		if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10) == 0 ) {
			if (button_struct.counters_btn[6] > WAIT) button_struct.btn_L = PRESSED_LONG;
			else button_struct.btn_L = PRESSED;
		}
		else button_struct.btn_L = IDLE;

		if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11) == 0 ) {
			if (button_struct.counters_btn[7] > WAIT) button_struct.btn_U = PRESSED_LONG;
			else button_struct.btn_U = PRESSED;
		}
		else button_struct.btn_U	= IDLE;

		if (button_struct.btn_U == PRESSED && button_struct.counters_btn[7] < 2 && flag_m.flag_m1 == 0){ //U
			Menu_Navigate(MENU_PREVIOUS);
			flag_m.flag_m1 = 1;
		}
		else flag_m.flag_m1 = 0;

		if (button_struct.btn_D == PRESSED && button_struct.counters_btn[4] < 2 && flag_m.flag_m2 == 0){ //D
			Menu_Navigate(MENU_NEXT);
			flag_m.flag_m2 = 1;
		}
		else flag_m.flag_m2 = 0;

		if (button_struct.btn_L == PRESSED && button_struct.counters_btn[6] < 2 && flag_m.flag_m3 == 0){ //L
			Menu_Navigate(MENU_PARENT);
			flag_m.flag_m3 = 1;
		}
		else flag_m.flag_m3 = 0;

		if (button_struct.btn_R == PRESSED && button_struct.counters_btn[5] < 2 && flag_m.flag_m4 == 0){ //R
			Menu_Navigate(MENU_CHILD);
			flag_m.flag_m4 = 1;
		}
		else flag_m.flag_m4 = 0;

		if (button_struct.btn_A == PRESSED && button_struct.counters_btn[0] < 2 && flag_m.flag_m5 == 0){ //A
			Menu_EnterCurrentItem();
			flag_m.flag_m5 = 1;
		}
		else flag_m.flag_m5 = 0;

}

void button_exti (uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_7 || GPIO_PIN_8 || GPIO_PIN_9 || GPIO_PIN_15 || GPIO_PIN_10 || GPIO_PIN_11 || GPIO_PIN_12 ) button_update();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  //UNUSED(GPIO_Pin);
  button_exti(GPIO_Pin);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}
