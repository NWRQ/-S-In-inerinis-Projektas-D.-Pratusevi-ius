#include "LCD1602.h"
#include "stm32l0xx_hal.h"

void LCD_Init(void) {
    HAL_Delay(20);
    LCD_SendCommand(0x33);
    HAL_Delay(20);
		LCD_SendCommand(0x32);  // Perejimas i 4bit
		HAL_Delay(20);
    LCD_SendCommand(0x28);  // 4-bit, 2 eilutes
    LCD_SendCommand(0x0C);  // Ekranas ON, kursorius OFF
    LCD_SendCommand(0x06);  // Kursorius juda i dešine
    LCD_SendCommand(0x01);  // Išvalyti ekrana
    HAL_Delay(20);
}

void LCD_SendCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(RS_PORT, RS_PIN, GPIO_PIN_RESET); // Command režimas
    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_RESET);

    // Aukštesni 4 bitai
    HAL_GPIO_WritePin(D4_PORT, D4_PIN, (cmd >> 4) & 0x01);
    HAL_GPIO_WritePin(D5_PORT, D5_PIN, (cmd >> 5) & 0x01);
    HAL_GPIO_WritePin(D6_PORT, D6_PIN, (cmd >> 6) & 0x01);
    HAL_GPIO_WritePin(D7_PORT, D7_PIN, (cmd >> 7) & 0x01);

    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_SET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);

    // Žemesni 4 bitai
    HAL_GPIO_WritePin(D4_PORT, D4_PIN, (cmd >> 0) & 0x01);
    HAL_GPIO_WritePin(D5_PORT, D5_PIN, (cmd >> 1) & 0x01);
    HAL_GPIO_WritePin(D6_PORT, D6_PIN, (cmd >> 2) & 0x01);
    HAL_GPIO_WritePin(D7_PORT, D7_PIN, (cmd >> 3) & 0x01);

    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_SET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);

}

void LCD_SendData(uint8_t data) {
    HAL_GPIO_WritePin(RS_PORT, RS_PIN, GPIO_PIN_SET); // Data režimas
    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_RESET);

    // Aukštesni 4 bitai
    HAL_GPIO_WritePin(D7_PORT, D7_PIN, (data >> 7) & 0x01);
    HAL_GPIO_WritePin(D6_PORT, D6_PIN, (data >> 6) & 0x01);
    HAL_GPIO_WritePin(D5_PORT, D5_PIN, (data >> 5) & 0x01);
    HAL_GPIO_WritePin(D4_PORT, D4_PIN, (data >> 4) & 0x01);

    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_RESET);
    HAL_Delay(10);

    // Žemesni 4 bitai
    HAL_GPIO_WritePin(D7_PORT, D7_PIN, (data >> 3) & 0x01);
    HAL_GPIO_WritePin(D6_PORT, D6_PIN, (data >> 2) & 0x01);
    HAL_GPIO_WritePin(D5_PORT, D5_PIN, (data >> 1) & 0x01);
    HAL_GPIO_WritePin(D4_PORT, D4_PIN, (data >> 0) & 0x01);

    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(E_PORT, E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);

}

void LCD_SendString(char *str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01);
    HAL_Delay(10);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t pos = (row == 0) ? 0x80 : 0xC0;
    LCD_SendCommand(pos + col);
}
