#ifndef __SSD1306_CONF_H__
#define __SSD1306_CONF_H__

#define SSD1306_SPI_PORT        hspi1

// Mirror the screen if needed
// #define SSD1306_MIRROR_VERT
// #define SSD1306_MIRROR_HORIZ

// Set inverse color if needed
// # define SSD1306_INVERSE_COLOR

// Include only needed fonts
#define SSD1306_INCLUDE_FONT_6x8
#define SSD1306_INCLUDE_FONT_7x10
#define SSD1306_INCLUDE_FONT_11x18
#define SSD1306_INCLUDE_FONT_16x26

#define SSD1306_WIDTH           132
#define SSD1306_HEIGHT          64

//#define STM32_COOCOX
#define STM32_CUBE

#ifdef STM32_CUBE

#define SSD1306_CS_Port         GPIOC
#define SSD1306_CS_Pin          GPIO_PIN_4
#define SSD1306_DC_Port         GPIOA
#define SSD1306_DC_Pin          GPIO_PIN_6
#define SSD1306_Reset_Port      GPIOA
#define SSD1306_Reset_Pin       GPIO_PIN_4

#define RESET_CS										LL_GPIO_ResetOutputPin(SSD1306_CS_Port, SSD1306_CS_Pin)
#define SET_CS											LL_GPIO_SetOutputPin(SSD1306_CS_Port, SSD1306_CS_Pin)
#define RESET_DC										LL_GPIO_ResetOutputPin(SSD1306_DC_Port, SSD1306_DC_Pin)
#define SET_DC											LL_GPIO_SetOutputPin(SSD1306_DC_Port, SSD1306_DC_Pin)
#define	RESET_PORT										LL_GPIO_ResetOutputPin(SSD1306_Reset_Port, SSD1306_Reset_Pin)
#define SET_PORT										LL_GPIO_SetOutputPin(SSD1306_Reset_Port, SSD1306_Reset_Pin)
#define CHECK_TXE_FLAG 									LL_SPI_IsActiveFlag_TXE(SPI1)
#define SPI_SEND										LL_I2S_TransmitData16(SPI1,send_data)

#define Delay 											HAL_Delay
#endif

#endif /* __SSD1306_CONF_H__ */
