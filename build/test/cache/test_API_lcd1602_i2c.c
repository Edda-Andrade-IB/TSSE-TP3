#include "build/test/mocks/mock_stm32_hal_funciones.h"
#include "/home/edda/Documentos/CESE/TSSE/TP3/API_lcd1602_i2c/test/support/Unity/src/unity.h"
#include "test/../src/API_lcd1602_i2c.h"














 HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)

{

    uint32_t freqrange, pclk1;





    hi2c->Instance->CR1 |= (0x1UL << (15U));

    hi2c->Instance->CR1 &= ~(0x1UL << (15U));





    pclk1 = 0;





    freqrange = 5;













    hi2c->ErrorCode = 0x00000000U;

    hi2c->State = HAL_I2C_STATE_READY;

    hi2c->PreviousState = ((uint32_t)(HAL_I2C_MODE_NONE));

    hi2c->Mode = HAL_I2C_MODE_NONE;



    return HAL_OK;

}



HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c) {



    hi2c->State = HAL_I2C_STATE_BUSY;

    hi2c->ErrorCode = 0x00000000U;

    hi2c->State = HAL_I2C_STATE_RESET;

    hi2c->PreviousState = ((uint32_t)(HAL_I2C_MODE_NONE));

    hi2c->Mode = HAL_I2C_MODE_NONE;









    return HAL_OK;

}



I2C_HandleTypeDef *hi2c1;



void setUp(void)

{

   HAL_I2C_Init(hi2c1);

}



void tearDown(void)

{

   HAL_I2C_DeInit(hi2c1);

}



void test_MX_I2C1_Init_Success(void) {





    HAL_I2CEx_ConfigAnalogFilter_CMockExpectAndReturn(83, hi2c1, 0x00000000U, HAL_OK);

    HAL_I2CEx_ConfigDigitalFilter_CMockExpectAndReturn(84, hi2c1, 0, HAL_ERROR);





    MX_I2C1_Init();





}
