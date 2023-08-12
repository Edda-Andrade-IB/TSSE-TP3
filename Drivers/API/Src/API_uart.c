/*
 * API_uart.c
 *
 *  Created on: Jul 28, 2023
 *      Author: nico
 */

#include "API_uart.h"
#include "main.h"
#include "stm32f4xx_nucleo_144.h"
#include <stdio.h>  // For printf
#include <string.h> // For strlen

/* Definition for USARTx clock resources */
#define BAUD_RATE 9600
#define WORD_LENGTH UART_WORDLENGTH_9B
#define STOP_BITS UART_STOPBITS_1
#define PARITY UART_PARITY_ODD
#define FLOW_CONTROL UART_HWCONTROL_NONE
#define MODE UART_MODE_TX_RX

#define UART_TIMEOUT_MS 0xFFFFFFFF /* 3 seconds */
#define BUFFER_SIZE 17

// TODO(Nico):
typedef enum {
	ACCUMULATING, DONE,
} uartState_t;

static UART_HandleTypeDef UartHandle;
static uartState_t current_state = ACCUMULATING;
static char ACCUMULATE_BUFFER[BUFFER_SIZE];
static char RETURN_BUFFER[BUFFER_SIZE];
static char readed_char;

static void appendCharToString(char *str, char c);

static const char* const ParityAsString(uint32_t parity) {
	const char *parity_str;
	switch (PARITY) {
	case UART_PARITY_NONE:
		parity_str = "NONE";
		break;
	case UART_PARITY_EVEN:
		parity_str = "EVEN";
		break;
	case UART_PARITY_ODD:
		parity_str = "ODD";
		break;
	default:
		parity_str = "ERROR!";
	}
	return parity_str;
}

static const char* const FlowConstrolAsString(uint32_t flow_control) {
	const char *flow_as_str;
	switch (flow_control) {
	case UART_HWCONTROL_NONE:
		flow_as_str = "NONE";
		break;
	case UART_HWCONTROL_RTS:
		flow_as_str = "RTS";
		break;
	case UART_HWCONTROL_CTS:
		flow_as_str = "CTS";
		break;
	case UART_HWCONTROL_RTS_CTS:
		flow_as_str = "RTS/CTS";
		break;
	default:
		flow_as_str = "ERROR!";
	}
	return flow_as_str;
}

bool_t uartInit() {
	bool_t return_value = true;

	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
	 - Word Length = 8 Bits (7 data bit + 1 parity bit) :
	 BE CAREFUL : Program 7 data bits + 1 parity bit in PC
	 HyperTerminal
	 - Stop Bit    = One Stop bit
	 - Parity      = ODD parity
	 - BaudRate    = 9600 baud
	 - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance = USARTx;
	UartHandle.Init.BaudRate = BAUD_RATE;
	UartHandle.Init.WordLength = WORD_LENGTH;
	UartHandle.Init.StopBits = STOP_BITS;
	UartHandle.Init.Parity = PARITY;
	UartHandle.Init.HwFlowCtl = FLOW_CONTROL;
	UartHandle.Init.Mode = MODE;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) == HAL_OK) {
		const char *conf_message = "UART configuration:\n"
				"\t BaudRate:     %d\n\r"
				"\t Word length:  %d\n\r"
				"\t StopBits:     %d\n\r"
				"\t Parity:       %s\n\r"
				"\t Flow control: %s\n\r";

		const char *const parity = ParityAsString(PARITY);
		const char *const flow_constrol = FlowConstrolAsString(FLOW_CONTROL);

		char message[256];

		sprintf(message, conf_message, BAUD_RATE, WORD_LENGTH, STOP_BITS,
				parity, flow_constrol);

		uartSendString((uint8_t*) message);

		// Enable interruoptions
		HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
		return_value = HAL_UART_Receive_IT(&UartHandle, (uint8_t*) &readed_char,
				sizeof(char)) == HAL_OK;

	} else {
		return_value = false;
	}

	/* Initialization Error */
	return return_value;
}

void uartSendString(uint8_t *pstring) {
	size_t size = strlen((char*) pstring);
	HAL_UART_Transmit(&UartHandle, pstring, size, UART_TIMEOUT_MS);
}

void uartSendStringSize(uint8_t *pstring, uint16_t size) {
	HAL_UART_Transmit(&UartHandle, pstring, size, UART_TIMEOUT_MS);
}

void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {
	HAL_UART_Receive(&UartHandle, pstring, size, UART_TIMEOUT_MS);
}

// UART receive complete callback
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	static uint8_t str_size = 0;
	++str_size;
	if (readed_char == '\r' || str_size == BUFFER_SIZE - 1) {

		if (readed_char != '\r') {
			appendCharToString(ACCUMULATE_BUFFER, readed_char);
		}
		memset(RETURN_BUFFER, '\0', BUFFER_SIZE);
		strcpy(RETURN_BUFFER, ACCUMULATE_BUFFER);
		memset(ACCUMULATE_BUFFER, '\0', BUFFER_SIZE);

		current_state = DONE;
		str_size = 0;
	} else {
		appendCharToString(ACCUMULATE_BUFFER, readed_char);

	}

	// Wait on non clocking mode for another char.
	HAL_UART_Receive_IT(&UartHandle, (uint8_t*) &readed_char, sizeof(char));
}

const char* readString(void) {
	const char *return_value;
	switch (current_state) {
	case ACCUMULATING:
		return_value = NULL;
		break;
	case DONE:
		return_value = RETURN_BUFFER;
		break;
	}
	current_state = ACCUMULATING;
	return return_value;
}

void USART3_IRQHandler(void) {
	HAL_UART_IRQHandler(&UartHandle);
}

static void appendCharToString(char *str, char c) {
	int length = strlen(str);
	str[length] = c;
	str[length + 1] = '\0';
}
