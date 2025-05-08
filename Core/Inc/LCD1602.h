#ifndef HD44780_H_
#define HD44780_H_

#include "stm32l0xx_hal.h"

// LCD PINU APRAŠYMAS
#define RS_PORT GPIOB
#define RS_PIN  GPIO_PIN_14
#define E_PORT  GPIOB
#define E_PIN   GPIO_PIN_13

#define D4_PORT GPIOB
#define D4_PIN  GPIO_PIN_11
#define D5_PORT GPIOB
#define D5_PIN  GPIO_PIN_2
#define D6_PORT GPIOB
#define D6_PIN  GPIO_PIN_1
#define D7_PORT GPIOB
#define D7_PIN  GPIO_PIN_15

// Funkciju deklaracijos
void LCD_Init(void);
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_SendString(char *str);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif /* HD44780_H_ */
