/*
 * API_lcd1602_i2c.c
 *
 *  Created on: Aug 9, 2023
 *      Author: nico
 */

#include "API_lcd1602_i2c.h"
#include "stm32f4xx_hal.h" // For HAL_GetTick()
#include <string.h>

#define I2C_TIMEOUT 1000
#define DISPLAY_SIZE 20
#define BUFFER_SIZE 256

typedef enum {
	NO_ANIMATION, SLIDE, NUM_DISPLAY_ALGORITHMS,
} display_algorithm;

static I2C_HandleTypeDef hi2c1;
static display_algorithm current_mode = 0;
static char DISPLAY_BUFFER[DISPLAY_SIZE];
static char TEXT_BUFFER[BUFFER_SIZE];

static void MX_I2C1_Init(void);

static void LCD1602_CursorPosition(uint8_t row, uint8_t col);
static void LCD1602_SendCommand(uint8_t command);
static void LCD1602_SendData(uint8_t data);

static void LCD1602_NoAnimationPrint(void);
static void LCD1602_SlidePrint(void);

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

void LCD1602_AddToBuffer(const char *pString) {
  LCD1602_CursorPosition(0, 0);
	strcpy(DISPLAY_BUFFER, pString);
  /* memset(DISPLAY_BUFFER, ' ', BUFFER_SIZE); */

	LCD1602_NoAnimationPrint();
}

void LCD1602_PrintMode(uint8_t mode) {
	if (mode < NUM_DISPLAY_ALGORITHMS) {
		current_mode = (display_algorithm) mode;
	}
}

void LCD1602_FSM_Update() {
	switch (current_mode) {
	case NO_ANIMATION:
		LCD1602_NoAnimationPrint();
		break;
	case SLIDE:
		LCD1602_SlidePrint();
		break;
	case NUM_DISPLAY_ALGORITHMS:
	default:
		// TODO(Nico): Handle this
		break;
	}
}

static void LCD1602_CursorPosition(uint8_t row, uint8_t col) {
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

static void LCD1602_SendCommand(uint8_t command) {
	uint8_t data[4];
	data[0] = (command & 0xF0) | 0x0C;        // High nibble with backlight ON
	data[1] = (command & 0xF0) | 0x08;        // High nibble with backlight OFF
	data[2] = ((command & 0x0F) << 4) | 0x0C; // Low nibble with backlight ON
	data[3] = ((command & 0x0F) << 4) | 0x08; // Low nibble with backlight OFF
	HAL_I2C_Master_Transmit(&hi2c1, 0x27 << 1, data, sizeof(data), I2C_TIMEOUT);
	HAL_Delay(2);
}

static void LCD1602_SendData(uint8_t data) {
	uint8_t dat = (data & 0xF0) | 0x0D; // High nibble with backlight ON
	HAL_I2C_Master_Transmit(&hi2c1, 0x27 << 1, &dat, 1, I2C_TIMEOUT);
	dat = (data & 0xF0) | 0x09; // High nibble with backlight OFF
	HAL_I2C_Master_Transmit(&hi2c1, 0x27 << 1, &dat, 1, I2C_TIMEOUT);
	dat = ((data & 0x0F) << 4) | 0x0D; // Low nibble with backlight ON
	HAL_I2C_Master_Transmit(&hi2c1, 0x27 << 1, &dat, 1, I2C_TIMEOUT);
	dat = ((data & 0x0F) << 4) | 0x09; // Low nibble with backlight OFF
	HAL_I2C_Master_Transmit(&hi2c1, 0x27 << 1, &dat, 1, I2C_TIMEOUT);
}

static void LCD1602_NoAnimationPrint(void) {
	const char *pString = DISPLAY_BUFFER;
	while (*pString) {
		LCD1602_SendData(*pString++);
	}
}

static void LCD1602_SlidePrint(void) {
}

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
