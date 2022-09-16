/*
 * button.h
 *
 *  Created on: 7 сент. 2022 г.
 *      Author: Muharlyamov
 */

#ifndef BUTTON_INC_BUTTON_H_
#define BUTTON_INC_BUTTON_H_

#define PRESSED_LONG 2
#define PRESSED 1
#define IDLE 0
#define WAIT 200
//#define PREVIOS

#include "main.h"
#include "stm32f4xx_it.h"

void button_counter ();
void button_update();
void button_exti (uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

struct btn_struct {
	 uint8_t btn_A;
	 uint8_t btn_B;
	 uint8_t btn_X;
	 uint8_t btn_Y;
	 uint8_t btn_D;
	 uint8_t btn_R;
	 uint8_t btn_L;
	 uint8_t btn_U;
	 uint16_t counters_btn[8];
 };

extern struct btn_struct button_struct;
#endif /* BUTTON_INC_BUTTON_H_ */




