/*
 * API_lcd1602_i2c.h
 *
 *  Created on: Aug 9, 2023
 *      Author: nico
 */

#ifndef API_INC_API_LCD1602_I2C_H_
#define API_INC_API_LCD1602_I2C_H_

#include <string.h>
#include <stdint.h>

void LCD1602_Init(void);
void LCD1602_SendCommand(uint8_t command);
void LCD1602_SendData(uint8_t data);
void LCD1602_Print(const char *text);

#endif /* API_INC_API_LCD1602_I2C_H_ */
