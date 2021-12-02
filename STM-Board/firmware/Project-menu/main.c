#include "stm32f4xx_rcc.h"
#include "main.h"
#include "menu.h"
#include "game.h"

volatile uint32_t counter = 0;
volatile uint32_t nCount = 0;
volatile uint32_t menuPressed = 0;

unsigned int readADC(uint8_t channel);
unsigned int result = 0;

extern uint16_t res = 0;
extern uint16_t enemy_start_time = 0;
extern uint16_t adcadc = 0;

uint8_t flag_menu = 0;

//--------------------------------------------------------------------------------------------------------
void main()
{
	GPIO_INIT();
	TIM_INIT();
	NVIC_INIT();
	SPI_INIT();
	ADC_INIT();
	ssd1306_Init();
	//splashScreen(); //draw_vin
	enemy_start_time = millis();
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);

	while (1)
	{
		I2C_StartTransmission(I2C_TypeDef* I2Cx, uint8_t transmissionDirection,  uint8_t slaveAddress);
		I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data);
		I2C_ReadData(I2C_TypeDef* I2Cx);
		I2C_EndTransmission(I2C_TypeDef* I2Cx);

		adc_rand();
		//updateGame();

      /*
      	 if (flag_menu == 1)	updateGame();
		 else if (flag_menu == 2) menu2();
		 else if (flag_menu == 3) menu3();
		 else if (flag_menu == 4) menu4();
		 else MENU_UPDATE();
      */
	}
}
//--------------------------------------------------------------------------------------------------------
void adc_rand()
{
	ADC2->CR2 |= ADC_CR2_SWSTART; 		//start ADC
    while ((ADC2->SR & ADC_SR_EOC)==0);	//End of conversion
    ADC2->SR = 0; 						//ADC status register
    res = (ADC2->DR); 					//ADC regular data register
    res = res % 10;
}

void ADC_INIT()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &= ~ GPIO_MODER_MODER0;
	GPIOA->MODER |= GPIO_MODER_MODER0;

	RCC->APB2ENR |=RCC_APB2ENR_ADC2EN;	//clock enable
	ADC2->CR2 &= ~ ADC_CR2_EXTEN;		//external trigger disconnection
	ADC2->SQR3  &= ~ ADC_SQR3_SQ1;		//enable channel 0 first conversion //  right edge
	ADC2->CR2 |= ADC_CR2_CONT;			// continuous conversion
    ADC2->CR2 |= ADC_CR2_ADON;			// on ADC
}
//--------------------------------------------------------------------------------------------------------
void TIM4_IRQHandler()
{
   	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
//--------------------------------------------------------------------------------------------------------
uint32_t millis() {
  return counter;
}
//--------------------------------------------------------------------------------------------------------
void TIM_INIT()
{
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Prescaler = 1600 - 1;
	TIM_InitStructure.TIM_Period = 10;
	TIM_TimeBaseInit(TIM7, &TIM_InitStructure);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM7, ENABLE);
}
//--------------------------------------------------------------------------------------------------------
void NVIC_INIT()
{
	NVIC_InitTypeDef NVIC_IniT;
	NVIC_IniT.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_IniT.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_IniT.NVIC_IRQChannelSubPriority = 0;
	NVIC_IniT.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_IniT);
}
//--------------------------------------------------------------------------------------------------------
void TIM7_IRQHandler(void)
{
	counter++;
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}
//--------------------------------------------------------------------------------------------------------
void GPIO_INIT()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	// ST1 (PB15) - RED   ST2 (PB14) - GREEN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	// PB2;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	// BTN7 (PC8), BTN8 (PC9), BTN2 (PC10), BTN3 (PC11), BTN4 (PC12), BTN6 (PC7);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	// BTN5 (PB12), BTN0 (PB8);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	// BTN1 (PA15)
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
//--------------------------------------------------------------------------------------------------------
