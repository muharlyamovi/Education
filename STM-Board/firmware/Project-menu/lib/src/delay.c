#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "delay.h"

void Delay(uint32_t ms)
{
        uint32_t time = millis();
        while ((millis() - time) < ms) {}
}

//void Delay(uint32_t ms)
//{
//        volatile uint32_t nCount;
//        RCC_ClocksTypeDef RCC_Clocks;
//        RCC_GetClocksFreq (&RCC_Clocks);
//        nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
//        for (; nCount!=0; nCount--);
//}

void DelayMC(uint32_t mc)
{
        volatile uint32_t nCount;
        RCC_ClocksTypeDef RCC_Clocks;
        RCC_GetClocksFreq (&RCC_Clocks);

        nCount=(RCC_Clocks.HCLK_Frequency/10000000)*mc;
        for (; nCount!=0; nCount--);
}


volatile uint32_t delay = 0;

void SysTick_Handler (void)
{
delay++;
}






