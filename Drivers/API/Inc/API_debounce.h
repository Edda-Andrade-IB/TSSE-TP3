/*
 * API_debounce.h
 *
 *  Created on: Jul 23, 2023
 *      Author: Nicolas Iriarte
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "API_delay.h" // bool_t

// Define the callback function signature
typedef void (*DebounceCallback)(void);

/**
 * SetUp the initial state for the FSM.
 */
void debounceFSM_init(void);

/**
 * This function must be called continuously. It will check the button state and the
 * exposed button state. It will update the state if needed.
 */
void debounceFSM_update(void);

/**
 * Return if the button is pressed or not.
 */
bool_t readKey(void);

/**
 * Set a callback to be executed the the ButtonPressed/ButtonReleased event
 * happen. This is when the internal FSM changes from one state to another.
 *
 * If a previous callback exists, this function will override the old one a no
 * notification will be emitted.
 *
 * If you want to remove a callback use as argument of the function `NULL`.
 */
void setPressedCallback(DebounceCallback callback);
void setReleasedCallback(DebounceCallback callback);

#endif /* API_INC_API_DEBOUNCE_H_ */
