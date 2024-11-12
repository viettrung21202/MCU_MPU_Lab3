/*
 * button.c
 *
 *  Created on: Oct 7, 2022
 *      Author: dell
 */

#include "button.h"

// Initialize variables for vibration handling, and button handling in two modes (normal and hold)
int KeyReg0[NUM_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg1[NUM_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg2[NUM_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg3[NUM_OF_BUTTONS] = {NORMAL_STATE};

// Initialize flags for each button: button_flag (normal press) and buttonlong_flag (long press)
int button_flag[NUM_OF_BUTTONS] = {0};
int buttonlong_flag[NUM_OF_BUTTONS] = {0};

// Initialize cycle counter variables to determine two possible events of the push button
int TimeOutForKeyPress[NUM_OF_BUTTONS] = {0};

int isButtonPressed(int index) {
	if (button_flag[index] == 1) {
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}



void getKeyInput() {
	for (int i = 0; i < NUM_OF_BUTTONS; i++) {
		KeyReg0[i] = KeyReg1[i];	// Vibration handling
		KeyReg1[i] = KeyReg2[i];

		// Read input from button (3 statuses)
		if (i == 0) {
			KeyReg2[i] = HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin);
		}
		else if (i == 1) {
			KeyReg2[i] = HAL_GPIO_ReadPin(INC_GPIO_Port, INC_Pin);
		}
		else if (i == 2) {
			KeyReg2[i] = HAL_GPIO_ReadPin(SET_GPIO_Port, SET_Pin);
		}

		// Input handling
		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg3[i] != KeyReg2[i]){
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg2[i] == PRESSED_STATE){
					button_flag[i] = 1;
					if (buttonlong_flag[i] == 0) {
						TimeOutForKeyPress[i] = 2000 / TIME_CYCLE; // Set time to 2 seconds (condition for longkeyPress event to appear)
					}
					else {
						TimeOutForKeyPress[i] = 250 / TIME_CYCLE;  // Set time 0.25s (status changes every 0.25s if button is long-pressed)
					}
				}
			} else {
				TimeOutForKeyPress[i]--;
				// If after the first TimeOutForKeyPress time (2s) the button is still held, then buttonlong_flag[i] will be 1, otherwise it will be 0.
				if (TimeOutForKeyPress[i] == 0){
					KeyReg3[i] = NORMAL_STATE;
					buttonlong_flag[i] = 1;
				}
			}
		}
		else {
			buttonlong_flag[i] = 0;
		}
	}
}

