#include "build/test/mocks/mock_stm32_hal_simplyfied.h"
#include "/home/edda/Documentos/CESE/TSSE/TP3/API_lcd1602_i2c/test/support/Unity/src/unity.h"
#include "test/../src/API_lcd1602_i2c.h"




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

    HAL_I2C_Init_CMockExpectAndReturn(28, &hi2c1, status);

    LCD1602_Init();

}
