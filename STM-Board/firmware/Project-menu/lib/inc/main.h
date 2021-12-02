#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_adc.h"
#include <misc.h>
#include <stdio.h>
#include <stdlib.h>
#include "delay.h"
#include "spi.h"
#include "i2c.h".h"
#include <math.h>
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "stm32f4xx_rng.h"
#include "game.h"
#include "menu.h"

uint8_t flag_menu;

uint32_t millis();

#endif
