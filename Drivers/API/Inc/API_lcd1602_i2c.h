/*
 * API_lcd1602_i2c.h
 *
 *  Created on: Aug 9, 2023
 *      Author: nico
 */

#ifndef API_INC_API_LCD1602_I2C_H_
#define API_INC_API_LCD1602_I2C_H_

#include <stdint.h>

void LCD1602_Init(void);
void LCD1602_AddToBuffer(const char *pString);
void LCD1602_PrintMode(uint8_t mode);
void LCD1602_FSM_Update();

#endif /* API_INC_API_LCD1602_I2C_H_ */
