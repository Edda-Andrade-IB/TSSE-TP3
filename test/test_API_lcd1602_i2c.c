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
//#include "../src/stm32_hal_simplyfied.h" //para compilar en la pc

I2C_HandleTypeDef hi2c1;


void setUp(void)
{
   HAL_I2C_Init(&hi2c1);
}

void tearDown(void)
{
   
}

void test_MX_I2C1_Init_Success(void) {
   
    HAL_I2C_Init_ExpectAndReturn(&hi2c1, HAL_OK);
    HAL_I2CEx_ConfigAnalogFilter_ExpectAndReturn(&hi2c1, I2C_ANALOGFILTER_ENABLE, HAL_OK);
    HAL_I2CEx_ConfigDigitalFilter_ExpectAndReturn(&hi2c1, 0, HAL_ERROR); // Debería fallar según la implementación

    // Llamar a la función a probar
    MX_I2C1_Init();

    // No se espera que haya ningún fallo, ya que los assert solo fallan si no cumplen
}