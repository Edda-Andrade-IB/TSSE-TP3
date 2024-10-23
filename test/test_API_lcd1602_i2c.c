/**
 * @file
 * @brief This file aims to test the functions of the API API_lcd1602_i2c.
 *
 * This file contains test cases and examples to validate the functionality
 * of the API_lcd1602_i2c library, ensuring that all functions perform as expected.
 */

#include "../src/API_lcd1602_i2c.h"
#include "/home/edda/Documentos/CESE/TSSE/TP3/API_lcd1602_i2c/test/support/Unity/src/unity.h"

#include "mock_stm32_hal_funciones.h"

//#include "../src/stm32_hal_funciones.h" //para compilar en la pc

//SE QUE QUEDA TOTALMENTE DESPROLIJO PONER ESTAS FUNCIONES AQUI PERO NO ENCONTRE FORMA DE HACERLAS PUBLICAS SIN QUE SE ME GENEREN INCLUSIONES RECURSIVAS
//Version simplificada de la HAL I2C Init para poder instanciar el puntero a la estructura I2C_HandleTypeDef

 HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)
{
    uint32_t freqrange, pclk1;

    /* Reset I2C */
    hi2c->Instance->CR1 |= I2C_CR1_SWRST;
    hi2c->Instance->CR1 &= ~I2C_CR1_SWRST;

    /* Get PCLK1 frequency */
    pclk1 = 0;

    /* Calculate frequency range */
    freqrange = 5;

    
    /* Enable I2C */
   

    /* Update state */
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->PreviousState = I2C_STATE_NONE;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c) {
    // Poner el estado del I2C como ocupado
    hi2c->State = HAL_I2C_STATE_BUSY;

    // Desactivar el reloj del periférico I2C
    

    // Llamar a la función de DeInit de bajo nivel (GPIO, CLOCK, NVIC)
    //HAL_I2C_MspDeInit(hi2c);

    // Reiniciar variables de estado
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->State = HAL_I2C_STATE_RESET;
    hi2c->PreviousState = I2C_STATE_NONE;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    // Desbloquear


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
   
    
    HAL_I2CEx_ConfigAnalogFilter_ExpectAndReturn(hi2c1, I2C_ANALOGFILTER_ENABLE, HAL_OK);
    HAL_I2CEx_ConfigDigitalFilter_ExpectAndReturn(hi2c1, 0, HAL_ERROR); // Debería fallar según la implementación

    // Llamar a la función a probar
    MX_I2C1_Init();

    // No se espera que haya ningún fallo, ya que los assert solo fallan si no cumplen
}