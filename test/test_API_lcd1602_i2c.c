/**
 * @file
 * @brief Este archivo tiene como objetivo probar las funciones de la API API_lcd1602_i2c.
 *
 * Este archivo contiene casos de prueba y ejemplos para validar la funcionalidad
 * de la biblioteca API_lcd1602_i2c, asegurando que todas las funciones se desempeñen como se espera.
 */

#include "../src/API_lcd1602_i2c.h"
#include "unity.h"

#define I2C_TIMEOUT 1000
#define DISPLAY_SIZE 17
#define BUFFER_SIZE 256
#define SLIDE_TIME_MS 500
#define DEVICE_ADDRESS (0x27 << 1)


#include "mock_stm32_hal_funciones.h"



// #include "../src/stm32_hal_funciones.h" //para compilar en la pc

// SE QUE QUEDA TOTALMENTE DESPROLIJO PONER ESTAS FUNCIONES AQUI PERO NO ENCONTRE FORMA DE HACERLAS PUBLICAS SIN QUE SE ME GENEREN INCLUSIONES RECURSIVAS
// Versión simplificada de la HAL I2C Init para poder instanciar el puntero a la estructura I2C_HandleTypeDef

HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)
{
    uint32_t freqrange, pclk1;

    /* Reset I2C */
    //hi2c->Instance->CR1 |= I2C_CR1_SWRST;
    //hi2c->Instance->CR1 &= ~I2C_CR1_SWRST;

    /* Get PCLK1 frequency */
    pclk1 = 3;

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

HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c)
{
    // Poner el estado del I2C como ocupado
    hi2c->State = HAL_I2C_STATE_BUSY;

    // Desactivar el reloj del periférico I2C

    // Llamar a la función de DeInit de bajo nivel (GPIO, CLOCK, NVIC)
    // HAL_I2C_MspDeInit(hi2c);

    // Reiniciar variables de estado
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->State = HAL_I2C_STATE_RESET;
    hi2c->PreviousState = I2C_STATE_NONE;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    // Desbloquear

    return HAL_OK;
}

I2C_HandleTypeDef * hi2c1 = &(I2C_HandleTypeDef){0};

/**
 * @brief Configuración inicial para cada prueba.
 */
void setUp(void)
{
   // HAL_I2C_Init(&hi2c1);
}

/**
 * @brief Limpieza después de cada prueba.
 */
void tearDown(void)
{
   // HAL_I2C_DeInit(&hi2c1);
}

/**
 * @brief Prueba para la inicialización exitosa de MX_I2C1.
 */
void test_MX_I2C1_Init_Success(void)
{
   HAL_I2CEx_ConfigAnalogFilter_ExpectAndReturn(hi2c1, I2C_ANALOGFILTER_ENABLE, HAL_OK);
   HAL_I2CEx_ConfigDigitalFilter_ExpectAndReturn(hi2c1, 0, HAL_ERROR); // Debería fallar según la implementación

    // Llamar a la función a probar
    MX_I2C1_Init();

    // No se espera que haya ningún fallo, ya que los assert solo fallan si no cumplen
}

// /**
//  * @brief Prueba para enviar un comando al LCD1602.
//  *
//  * Esta prueba verifica que la función LCD1602_SendCommand envía correctamente
//  * un comando al LCD1602 utilizando la comunicación I2C.
//  */
// void test_LCD1602_SendCommand(void)
// {
//     uint8_t command = 0x28; // Comando de prueba

//     // Configurar las expectativas para las llamadas a HAL_I2C_Master_Transmit
//     uint8_t data[4];
//     data[0] = (command & 0xF0) | 0x0C;        // High nibble with backlight ON
//     data[1] = (command & 0xF0) | 0x08;        // High nibble with backlight OFF
//     data[2] = ((command & 0x0F) << 4) | 0x0C; // Low nibble with backlight ON
//     data[3] = ((command & 0x0F) << 4) | 0x08; // Low nibble with backlight OFF

//     HAL_I2C_Master_Transmit_ExpectAndReturn(&hi2c1, DEVICE_ADDRESS, data, sizeof(data), I2C_TIMEOUT, HAL_OK);
//     HAL_Delay_Expect(2);

//     // Llamar a la función a probar
//     LCD1602_SendCommand(command);
// }

// /**
//  * @brief Prueba para la inicialización del LCD1602.
//  *
//  * Esta prueba verifica que la función LCD1602_Init inicializa correctamente el LCD1602
//  * enviando los comandos adecuados y llamando a las funciones de retardo esperadas.
//  */
// void test_LCD1602_Init(void)
// {
//     // Configuramos las llamadas que espera HAL_Delay
//     HAL_Delay_Expect(50);
//     HAL_Delay_Expect(2);
//     HAL_Delay_Expect(2);
//     HAL_Delay_Expect(2);

//     // Llamar a la función a probar
//     LCD1602_Init();
// }

// /**
//  * @brief Prueba para agregar texto al buffer sin animación.
//  *
//  * Esta prueba verifica que la función LCD1602_AddToBuffer agrega correctamente
//  * una cadena de texto al buffer cuando el modo de animación es NO_ANIMATION.
//  */
// void test_LCD1602_AddToBuffer_NoAnimation(void)
// {
//     const char *testString = "Hello, World!";
//     current_mode = NO_ANIMATION;

//     // Llamar a la función a probar
//     LCD1602_AddToBuffer(testString);

//     // Verificar si el TEXT_BUFFER contiene la cadena de prueba
//     TEST_ASSERT_EQUAL_STRING(testString, TEXT_BUFFER);
// }

// /**
//  * @brief Prueba para agregar texto al buffer con animación de deslizamiento.
//  *
//  * Esta prueba verifica que la función LCD1602_AddToBuffer agrega correctamente
//  * una cadena de texto al buffer cuando el modo de animación es SLIDE.
//  */
// void test_LCD1602_AddToBuffer_Slide(void)
// {
//     const char *testString = "Hello, World!";
//     current_mode = SLIDE;

//     // Llamar a la función a probar
//     LCD1602_AddToBuffer(testString);

//     // Verificar si el TEXT_BUFFER contiene la cadena de prueba con espacios
//     char expectedBuffer[BUFFER_SIZE] = "                Hello, World!";
//     TEST_ASSERT_EQUAL_STRING(expectedBuffer, TEXT_BUFFER);
// }

// /**
//  * @brief Prueba para el modo de impresión del LCD1602.
//  *
//  * Esta prueba verifica que la función LCD1602_PrintMode cambia correctamente
//  * el modo de impresión del LCD1602 y maneja modos inválidos.
//  */
// void test_LCD1602_PrintMode(void)
// {
//     // Probar modo válido
//     LCD1602_PrintMode(SLIDE);
//     TEST_ASSERT_EQUAL(SLIDE, current_mode);

//     // Probar modo inválido
//     LCD1602_PrintMode(NUM_DISPLAY_ALGORITHMS);
//     TEST_ASSERT_EQUAL(DEFAULT_MODE, current_mode);
// }

// /**
//  * @brief Prueba para la impresión sin animación en el LCD1602.
//  *
//  * Esta prueba verifica que la función LCD1602_NoAnimationPrint imprime
//  * correctamente el contenido del buffer en el LCD1602 sin animación.
//  */
// void test_LCD1602_NoAnimationPrint(void)
// {
//     // Configurar el buffer de texto y el modo actual
//     const char *testString = "Hello, World!";
//     strcpy(TEXT_BUFFER, testString);
//     current_mode = NO_ANIMATION;

//     // Configurar las expectativas para las llamadas a HAL_I2C_Master_Transmit y HAL_Delay
//     uint8_t data[4];
//     for (size_t i = 0; i < strlen(testString); ++i)
//     {
//         data[0] = (testString[i] & 0xF0) | 0x0D;        // High nibble with backlight ON
//         data[1] = (testString[i] & 0xF0) | 0x09;        // High nibble with backlight OFF
//         data[2] = ((testString[i] & 0x0F) << 4) | 0x0D; // Low nibble with backlight ON
//         data[3] = ((testString[i] & 0x0F) << 4) | 0x09; // Low nibble with backlight OFF

//         HAL_I2C_Master_Transmit_ExpectAndReturn(&hi2c1, DEVICE_ADDRESS, &data[0], 1, I2C_TIMEOUT, HAL_OK);
//         HAL_I2C_Master_Transmit_ExpectAndReturn(&hi2c1, DEVICE_ADDRESS, &data[1], 1, I2C_TIMEOUT, HAL_OK);
//         HAL_I2C_Master_Transmit_ExpectAndReturn(&hi2c1, DEVICE_ADDRESS, &data[2], 1, I2C_TIMEOUT, HAL_OK);
//         HAL_I2C_Master_Transmit_ExpectAndReturn(&hi2c1, DEVICE_ADDRESS, &data[3], 1, I2C_TIMEOUT, HAL_OK);
//     }

//     // Llamar a la función a probar
//     LCD1602_NoAnimationPrint();

//     // Verificar si el DISPLAY_BUFFER contiene la cadena de prueba
//     TEST_ASSERT_EQUAL_STRING(testString, DISPLAY_BUFFER);
// }

// // Agregar la nueva prueba al main
// int main(void)
// {
//     UNITY_BEGIN();
//     TEST_RUN(test_MX_I2C1_Init_Success);
//     TEST_RUN(test_LCD1602_Init);
//     TEST_RUN(test_LCD1602_AddToBuffer_NoAnimation);
//     TEST_RUN(test_LCD1602_AddToBuffer_Slide);
//     TEST_RUN(test_LCD1602_PrintMode);
//     TEST_RUN(test_LCD1602_NoAnimationPrint);

//     return UNITY_END();
// }
// /**
//  * @brief Prueba para la actualización de la pantalla sin animación.
//  *
//  * Esta prueba verifica que la función LCD1602_FSM_UpdateDisplay actualiza
//  * correctamente la pantalla cuando el modo de animación es NO_ANIMATION.
//  */
// void test_LCD1602_FSM_UpdateDisplay_NoAnimation(void)
// {

//     // Llamar a la función a probar
//     LCD1602_FSM_UpdateDisplay();
// }

// /**
//  * @brief Prueba para la actualización de la pantalla con animación de deslizamiento.
//  *
//  * Esta prueba verifica que la función LCD1602_FSM_UpdateDisplay actualiza
//  * correctamente la pantalla cuando el modo de animación es SLIDE.
//  */
// void test_LCD1602_FSM_UpdateDisplay_Slide(void)
// {
//     current_mode = SLIDE;

//     // Mock de la función LCD1602_SlidePrint
//     LCD1602_SlidePrint_Expect();

//     // Llamar a la función a probar
//     LCD1602_FSM_UpdateDisplay();
// }

// /**
//  * @brief Prueba para cambiar al siguiente algoritmo de visualización.
//  *
//  * Esta prueba verifica que la función LCD1602_FSM_NextAlgorithm cambia
//  * correctamente al siguiente algoritmo de visualización.
//  */
// void test_LCD1602_FSM_NextAlgorithm(void)
// {
//     current_mode = NO_ANIMATION;

//     // Llamar a la función a probar
//     LCD1602_FSM_NextAlgorithm();

//     // Verificar si el modo actual se actualiza
//     TEST_ASSERT_EQUAL(SLIDE, current_mode);
//     TEST_ASSERT_EQUAL_STRING("Slide animation", TEXT_BUFFER);
// }

// /**
//  * @brief Prueba para desplazar una cadena a la izquierda.
//  *
//  * Esta prueba verifica que la función ShiftStringLeft desplaza correctamente
//  * una cadena de texto a la izquierda por un número dado de posiciones.
//  */
// void test_ShiftStringLeft(void)
// {
//     char testString[] = "Hello, World!";
//     ShiftStringLeft(testString, 2);
//     TEST_ASSERT_EQUAL_STRING("llo, World!", testString);
// }

// /**
//  * @brief Prueba para verificar si una cadena tiene caracteres.
//  *
//  * Esta prueba verifica que la función StringHasChars determina correctamente
//  * si una cadena de texto contiene caracteres no espaciales.
//  */
// void test_StringHasChars(void)
// {
//     TEST_ASSERT_TRUE(StringHasChars("Hello"));
//     TEST_ASSERT_FALSE(StringHasChars("     "));
// }

// /**
//  * @brief Prueba para llenar una cadena con un carácter específico.
//  *
//  * Esta prueba verifica que la función FillString llena correctamente una
//  * cadena de texto con un carácter específico hasta una longitud dada.
//  */
// void test_FillString(void)
// {
//     char testString[20] = "Hello";
//     FillString(testString, ' ', 10);
//     TEST_ASSERT_EQUAL_STRING("Hello     ", testString);
// }

// /**
//  * @brief Función principal para ejecutar todas las pruebas.
//  *
//  * Esta función ejecuta todas las pruebas definidas anteriormente utilizando
//  * el marco de pruebas Unity.
//  */
// int main(void)
// {
//     UNITY_BEGIN();

//     RUN_TEST(test_MX_I2C1_Init_Success);
//     RUN_TEST(test_LCD1602_Init);
//     RUN_TEST(test_LCD1602_AddToBuffer_NoAnimation);
//     RUN_TEST(test_LCD1602_AddToBuffer_Slide);
//     RUN_TEST(test_LCD1602_PrintMode);
//     RUN_TEST(test_LCD1602_FSM_UpdateDisplay_NoAnimation);
//     RUN_TEST(test_LCD1602_FSM_UpdateDisplay_Slide);
//     RUN_TEST(test_LCD1602_FSM_NextAlgorithm);
//     RUN_TEST(test_ShiftStringLeft);
//     RUN_TEST(test_StringHasChars);
//     RUN_TEST(test_FillString);

//     return UNITY_END();
// }
