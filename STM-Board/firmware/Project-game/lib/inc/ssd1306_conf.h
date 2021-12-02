#ifndef __SSD1306_CONF_H__
#define __SSD1306_CONF_H__



#define SSD1306_SPI_PORT        hspi1

#define SSD1306_CS_Port         GPIOC
#define SSD1306_CS_Pin          GPIO_Pin_4
#define SSD1306_DC_Port         GPIOA
#define SSD1306_DC_Pin          GPIO_Pin_6
#define SSD1306_Reset_Port      GPIOA
#define SSD1306_Reset_Pin       GPIO_Pin_4

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

#endif /* __SSD1306_CONF_H__ */
