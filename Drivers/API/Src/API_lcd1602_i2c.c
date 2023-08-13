/*
 * API_lcd1602_i2c.c
 *
 *  Created on: Aug 9, 2023
n *      Author: nico
 */

#include "API_lcd1602_i2c.h"
#include "stm32f4xx_hal.h" // For HAL_GetTick()
#include <stdbool.h>
#include <string.h>

#define I2C_TIMEOUT 1000
#define DISPLAY_SIZE 17
#define BUFFER_SIZE 256
#define SLIDE_TIME_MS 500
#define DEVICE_ADDRESS 0x27 << 1

typedef enum {
  NO_ANIMATION,
  SLIDE,
  NUM_DISPLAY_ALGORITHMS,
} display_algorithm;

#define DEFAULT_MODE NO_ANIMATION

typedef bool bool_t;

static I2C_HandleTypeDef hi2c1;
static display_algorithm current_mode = 0;
static char DISPLAY_BUFFER[DISPLAY_SIZE];
static char TEXT_BUFFER[BUFFER_SIZE];

/**
 * Initialize the I2C using the HAL provided funtions.
 */
static void MX_I2C1_Init(void);

/**
 * Set the cursor position to write.
 *
 * Valid numbers:
 * row = 0 or 1
 * col = from 0 to 15
 */
static void LCD1602_CursorPosition(uint8_t row, uint8_t col);

/**
 * Send a command. Useful for configuring the peripheric.
 */
static void LCD1602_SendCommand(uint8_t command);

/**
 * Send data through I2C, useful for sending chars.
 */
static void LCD1602_SendData(uint8_t data);

/**
 * Algorithm to print the data on the screen without animation.
 */
static void LCD1602_NoAnimationPrint(void);

/**
 * Algorithm to print the data on the screen with a slide animation.
 */
static void LCD1602_SlidePrint(void);

/**
 * Modify the string shifting all the characters `numElements` to the left.
 *
 * For example, Given the string "Hello World!" shifting two spaces will result
 * on "llo World!"
 */
static void ShiftStringLeft(char *string, int numElements);

/**
 * This function returns true if any char is present on the screen, false
 * otherwise.
 */
static bool_t StringHasChars(const char *string);

/**
 * Fill the string (if possible) whith `ch` until reach `up_to` length.
 */
static void FillString(char *string, char ch, uint32_t up_to);

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
  switch (current_mode) {
  case NO_ANIMATION:
    strcpy(TEXT_BUFFER, pString);
    break;
  case SLIDE:
    if (StringHasChars(TEXT_BUFFER)) {
      FillString(TEXT_BUFFER, ' ', strlen(TEXT_BUFFER) + DISPLAY_SIZE / 3);
    } else {
      memset(TEXT_BUFFER, ' ', DISPLAY_SIZE);
    }
    strcat(TEXT_BUFFER, pString);
    break;
  case NUM_DISPLAY_ALGORITHMS:
  default:
    // If we fail getting the current mode, default it to DEFAULT_MODE
    current_mode = DEFAULT_MODE;
    LCD1602_AddToBuffer(pString);
    break;
  }
}

void LCD1602_PrintMode(uint8_t mode) {
  if (mode < NUM_DISPLAY_ALGORITHMS) {
    current_mode = (display_algorithm)mode;
  }
}

void LCD1602_FSM_UpdateDisplay(void) {
  switch (current_mode) {
  case NO_ANIMATION:
    LCD1602_NoAnimationPrint();
    break;
  case SLIDE:
    LCD1602_SlidePrint();
    break;
  case NUM_DISPLAY_ALGORITHMS:
  default:
    // Try not failing, move to default MODE
    current_mode = DEFAULT_MODE;

    break;
  }
}

void LCD1602_FSM_NextAlgorithm(void) {
  current_mode = (current_mode + 1) % NUM_DISPLAY_ALGORITHMS;
  memset(&DISPLAY_BUFFER, '\0', DISPLAY_SIZE);
  memset(&TEXT_BUFFER, '\0', BUFFER_SIZE);

  char *mode_name = NULL;

  switch (current_mode) {
  case NO_ANIMATION:
    mode_name = "No animation";
    break;
  case SLIDE:
    mode_name = "Slide animation";
    break;
  case NUM_DISPLAY_ALGORITHMS:
  default:
    // Do not fail if invalid mode. Change to default one instead
    current_mode = DEFAULT_MODE;
    LCD1602_FSM_NextAlgorithm();
    break;
  }

  LCD1602_AddToBuffer(mode_name);
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
  /**
   * As we are using 4-bit communication, we must do some work on the data to be
   * sended.
   */
  uint8_t data[4];
  data[0] = (command & 0xF0) | 0x0C;        // High nibble with backlight ON
  data[1] = (command & 0xF0) | 0x08;        // High nibble with backlight OFF
  data[2] = ((command & 0x0F) << 4) | 0x0C; // Low nibble with backlight ON
  data[3] = ((command & 0x0F) << 4) | 0x08; // Low nibble with backlight OFF
  HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS, data, sizeof(data),
                          I2C_TIMEOUT);
  HAL_Delay(2);
}

static void LCD1602_SendData(uint8_t data) {
  /**
   * As we are using 4-bit communication, we must do some work on the data to be
   * sended. So, multiple calls to the HAL facility are done.
   */

  uint8_t dat = (data & 0xF0) | 0x0D; // High nibble with backlight ON
  HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS, &dat, 1, I2C_TIMEOUT);
  dat = (data & 0xF0) | 0x09; // High nibble with backlight OFF
  HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS, &dat, 1, I2C_TIMEOUT);
  dat = ((data & 0x0F) << 4) | 0x0D; // Low nibble with backlight ON
  HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS, &dat, 1, I2C_TIMEOUT);
  dat = ((data & 0x0F) << 4) | 0x09; // Low nibble with backlight OFF
  HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS, &dat, 1, I2C_TIMEOUT);
}

static void LCD1602_NoAnimationPrint(void) {
  LCD1602_CursorPosition(0, 0);
  int need_update = strncmp(DISPLAY_BUFFER, TEXT_BUFFER, DISPLAY_SIZE);

  if (need_update) {
    size_t length = strlen(TEXT_BUFFER);

    if (length < DISPLAY_SIZE) {
      FillString(TEXT_BUFFER, ' ', DISPLAY_SIZE - 1);
    }

    strncpy(DISPLAY_BUFFER, TEXT_BUFFER, DISPLAY_SIZE - 1);
    DISPLAY_BUFFER[DISPLAY_SIZE] = '\0';

    const char *pString = DISPLAY_BUFFER;
    while (*pString) {
      LCD1602_SendData(*pString++);
    }
  }
}

static void LCD1602_SlidePrint(void) {
  LCD1602_CursorPosition(0, 0);
  /* ShiftStringLeft(TEXT_BUFFER, 1); */
  /* strncpy(DISPLAY_BUFFER, TEXT_BUFFER, DISPLAY_SIZE); */
  /* DISPLAY_BUFFER[DISPLAY_SIZE - 1] = '\0'; */

  static uint32_t last_time_updated = 0;
  uint32_t current_time = HAL_GetTick();

  if ((current_time - last_time_updated) > SLIDE_TIME_MS) {
    ShiftStringLeft(TEXT_BUFFER, 1);
    last_time_updated = current_time;
  }

  int need_update = strncmp(DISPLAY_BUFFER, TEXT_BUFFER, DISPLAY_SIZE);

  if (need_update) {
    size_t length = strlen(TEXT_BUFFER);

    if (length < DISPLAY_SIZE) {
      FillString(TEXT_BUFFER, ' ', DISPLAY_SIZE - 1);
    }

    strncpy(DISPLAY_BUFFER, TEXT_BUFFER, DISPLAY_SIZE - 1);
    DISPLAY_BUFFER[DISPLAY_SIZE] = '\0';

    const char *pString = DISPLAY_BUFFER;
    while (*pString) {
      LCD1602_SendData(*pString++);
    }
  }
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
  assert(HAL_I2C_Init(&hi2c1) == HAL_OK);

  /** Configure Analogue filter
   */
  assert(HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) ==
         HAL_OK);

  /** Configure Digital filter
   */
  assert(HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK);
}

static void ShiftStringLeft(char *string, int numElements) {
  int length = strlen(string);
  if (numElements > length) {
    return;
  }

  for (int i = 0; i < length - numElements; i++) {
    string[i] = string[i + numElements];
  }

  string[length - numElements] = '\0';
}

static bool_t StringHasChars(const char *string) {
  while (*string) {
    if (*string != ' ') {
      return true;
    }
    string++; // Increment the pointer after the check
  }
  return false;
}

static void FillString(char *string, char ch, uint32_t up_to) {
  size_t length = strlen(string);

  for (int i = length; i < up_to; ++i) {
    string[i] = ch;
  }
  string[up_to] = '\0';
}
