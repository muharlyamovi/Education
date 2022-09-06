/*
 * menu.h
 *
 *  Created on: 5 сент. 2022 г.
 *      Author: Muharlyamov
 */

#ifndef MENU_INC_MENU_H_
#define MENU_INC_MENU_H_

#include "main.h"
#include "Game_1.h"

uint8_t BTNPressed;
uint8_t cursorY;
uint8_t flag_in;
uint8_t flag_up;
uint8_t flag_down;
extern volatile uint8_t flag_menu;

void MENU_GENERAL();
void MENU_SECOND();
void updateDir();
void BTN();

#endif /* MENU_INC_MENU_H_ */
