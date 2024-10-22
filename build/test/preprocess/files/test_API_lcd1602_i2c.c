#include "build/test/mocks/mock_stm32_hal_simplyfied.h"
#include "/home/edda/Documentos/CESE/TSSE/TP3/API_lcd1602_i2c/test/support/Unity/src/unity.h"
#include "test/../src/API_lcd1602_i2c.h"




extern I2C_HandleTypeDef hi2c1;





void setUp(void)

{

   HAL_I2C_Init(&hi2c1);

}



void tearDown(void)

{



}



void test_MX_I2C1_Init_Success(void) {



    HAL_I2C_Init_ExpectAndReturn(&hi2c1, HAL_OK);

    HAL_I2CEx_ConfigAnalogFilter_CMockExpectAndReturn(30, &hi2c1, 0x00000000U, HAL_OK);

    HAL_I2CEx_ConfigDigitalFilter_CMockExpectAndReturn(31, &hi2c1, 0, HAL_ERROR);





    MX_I2C1_Init();





}
