/*
 * API_lcd1602_i2c.c
 *
 *  Created on: Aug 9, 2023
 *      Author: nico
 */

#include "API_lcd1602_i2c.h"
#include "stm32f4xx_hal.h" // For HAL_GetTick()

#define I2C_TIMEOUT 1000
#define DISPLAY_SIZE 20
#define BUFFER_SIZE 256

I2C_HandleTypeDef hi2c1;

static void MX_I2C1_Init(void) {
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		// TODO: Handle error
		// Error_Handler();
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		// TODO: Handle error
		// Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK) {
		// TODO: Handle error
		// Error_Handler();
	}
}

void LCD1602_Init(void) {
	MX_I2C1_Init();
	// LCD initialization commands
	HAL_Delay(50); // Wait for LCD power-up

	LCD1602_SendCommand(0b00000010); // 4-bit mode
	HAL_Delay(2);

	// 4-bit initialization
	LCD1602_SendCommand(0b00101000); // 2 lines, 5x8 font
	LCD1602_SendCommand(0b00001000); // Display off
	LCD1602_SendCommand(0b00000001); // Clear display
	HAL_Delay(2);
	LCD1602_SendCommand(0b00000110); // Entry mode set: cursor moves to right
	LCD1602_SendCommand(0b00001100); // Display on, cursor off
	HAL_Delay(2);

}

void LCD1602_CursorPosition(uint8_t row, uint8_t col) {
	switch (row) {
	case 0:
		col |= 0x80;
		break;
	case 1:
		col |= 0xC0;
		break;
	}
	LCD1602_SendCommand(col);
}

void LCD1602_SendCommand(uint8_t command) {
	uint8_t data[4];
	data[0] = (command & 0xF0) | 0x0C; // High nibble with backlight ON
	data[1] = (command & 0xF0) | 0x08; // High nibble with backlight OFF
	data[2] = ((command & 0x0F) << 4) | 0x0C; // Low nibble with backlight ON
	data[3] = ((command & 0x0F) << 4) | 0x08; // Low nibble with backlight OFF
	HAL_I2C_Master_Transmit(&hi2c1, 0x27 << 1, data, sizeof(data), I2C_TIMEOUT);
	HAL_Delay(2);
}

void LCD1602_SendData(uint8_t data) {
	uint8_t dat = (data & 0xF0) | 0x0D; // High nibble with backlight ON
	HAL_I2C_Master_Transmit(&hi2c1, 0x27 << 1, &dat, 1, I2C_TIMEOUT);
	dat = (data & 0xF0) | 0x09; // High nibble with backlight OFF
	HAL_I2C_Master_Transmit(&hi2c1, 0x27 << 1, &dat, 1, I2C_TIMEOUT);
	dat = ((data & 0x0F) << 4) | 0x0D; // Low nibble with backlight ON
	HAL_I2C_Master_Transmit(&hi2c1, 0x27 << 1, &dat, 1, I2C_TIMEOUT);
	dat = ((data & 0x0F) << 4) | 0x09; // Low nibble with backlight OFF
	HAL_I2C_Master_Transmit(&hi2c1, 0x27 << 1, &dat, 1, I2C_TIMEOUT);
}

void LCD1602_Print(const char *text) {
	while (*text) {
		LCD1602_SendData(*text++);
	}
}

static void LCD1602_SlidePrint(const char *pString) {
	char display_buffer[BUFFER_SIZE];

	static uint32_t accumulated = 0;
	char *position = &display_buffer[0];

	// Only on init
	memset(display_buffer, ' ', 255);

	strcpy(display_buffer + DISPLAY_SIZE + accumulated, pString);
	accumulated += DISPLAY_SIZE + strlen(pString);

	for (int i = 0; *position != '\0'; ++i) {
//	    printf("Nico: '%s'\n", position);
		accumulated--;
		*(position) = ' '; // Clean buffer
		position++;
		HAL_Delay(200);
	}
	*position = ' ';
}
