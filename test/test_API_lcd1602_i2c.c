/**
 * @file
 * @brief This file aims to test the functions of the API API_lcd1602_i2c.
 *
 * This file contains test cases and examples to validate the functionality
 * of the API_lcd1602_i2c library, ensuring that all functions perform as expected.
 */

#include "../src/API_lcd1602_i2c.h"
#include "/home/edda/Documentos/CESE/TSSE/TP3/API_lcd1602_i2c/test/support/Unity/src/unity.h"
#include "mock_stm32_hal_simplyfied.h"
//#include "../src/stm32_hal_simplyfied.h"

extern I2C_HandleTypeDef hi2c1;

void setUp(void)
{

}

void tearDown(void)
{
}

void test_LCD1602_Init(void)
{
    HAL_StatusTypeDef status = HAL_OK;
    HAL_I2C_Init_ExpectAndReturn(&hi2c1, status);
    LCD1602_Init();
}
