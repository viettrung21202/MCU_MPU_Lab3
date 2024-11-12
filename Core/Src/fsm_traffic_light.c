/*
 * mode2.c
 *
 *  Created on: Nov 1, 2022
 *      Author: dell
 */

#include "fsm_traffic_light.h"

void fsm_traffic_light() {
	switch(status){

//----------------------------------------------------------------------------------------------
// MODE INIT
	case INIT:
		// Turn to mode 1
		status = MODE1;
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 1
	case MODE1:
		// Turn to period AUTO_REDL_GREENP
		status = AUTO_REDL_GREENP;

		// Landscape_RED va Portrait_GREEN are turned on
		HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, RESET);
		HAL_GPIO_WritePin(LA_GPIO_Port, LA_Pin, SET);
		HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, SET);
		HAL_GPIO_WritePin(PR_GPIO_Port, PR_Pin, SET);
		HAL_GPIO_WritePin(PA_GPIO_Port, PA_Pin, SET);
		HAL_GPIO_WritePin(PG_GPIO_Port, PG_Pin, RESET);

		// Initial setup and update value and display 7-segment LED
		counterL = 1;
		counterP = 1;
		index_led = 0;
		updateClockBufferMode1();
		update7SEG(index_led);

		// Set Timer
		setTimer(0, GREEN * 1000);	// Timer0 for AUTO_REDL_GREENP
		setTimer(1, 1000);			// Timer1 for updateClockBufferMode1
		setTimer(2, 250);			// Timer2 for update7SEG
		clearTimer(3);				// Timer3 for Blinking Led when increasing the traffic light duration (not used at mode 1)

		break;

	case AUTO_REDL_GREENP:
		// Landscape_RED and Portrait_GREEN are turned on
		HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, RESET);
		HAL_GPIO_WritePin(LA_GPIO_Port, LA_Pin, SET);
		HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, SET);
		HAL_GPIO_WritePin(PR_GPIO_Port, PR_Pin, SET);
		HAL_GPIO_WritePin(PA_GPIO_Port, PA_Pin, SET);
		HAL_GPIO_WritePin(PG_GPIO_Port, PG_Pin, RESET);
		// If timer_flag[0] == 1, turn to AUTO_REDL_AMBERP and set timer for the next case
		if (timer_flag[0] == 1) {
			status = AUTO_REDL_AMBERP;
			setTimer(0, AMBER * 1000);
		}
		// If timer_flag[1] == 1, update traffic light duration va reset the timer
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// If timer_flag[2] == 1, turn on the next 7-segment LED and reset the timer
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// If press the MODE button, the system turn to mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDL_AMBERP:
		// Landscape_RED and Portrait_AMBER are turned on
		HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, RESET);
		HAL_GPIO_WritePin(LA_GPIO_Port, LA_Pin, SET);
		HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, SET);
		HAL_GPIO_WritePin(PR_GPIO_Port, PR_Pin, SET);
		HAL_GPIO_WritePin(PA_GPIO_Port, PA_Pin, RESET);
		HAL_GPIO_WritePin(PG_GPIO_Port, PG_Pin, SET);
		// If timer_flag[0] == 1, turn to AUTO_REDP_GREENL and set timer for the next case
		if (timer_flag[0] == 1) {
			status = AUTO_REDP_GREENL;
			setTimer(0, GREEN * 1000);
		}
		// If timer_flag[1] == 1, update traffic light duration va reset the timer
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// If timer_flag[2] == 1, turn on the next 7-segment LED and reset the timer
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// If press the MODE button, the system turn to mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDP_GREENL:
		// Portrait_RED and Landscape_GREEN are turned on
		HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, SET);
		HAL_GPIO_WritePin(LA_GPIO_Port, LA_Pin, SET);
		HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, RESET);
		HAL_GPIO_WritePin(PR_GPIO_Port, PR_Pin, RESET);
		HAL_GPIO_WritePin(PA_GPIO_Port, PA_Pin, SET);
		HAL_GPIO_WritePin(PG_GPIO_Port, PG_Pin, SET);
		// If timer_flag[0] == 1, turn to AUTO_REDP_AMBERL and set timer for the next case
		if (timer_flag[0] == 1) {
			status = AUTO_REDP_AMBERL;
			setTimer(0, AMBER * 1000);
		}
		// If timer_flag[1] == 1, update traffic light duration va reset the timer
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// If timer_flag[2] == 1, turn on the next 7-segment LED and reset the timer
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// If press the MODE button, the system turn to mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDP_AMBERL:
		// Portrait_RED and Landscape_AMBER are turned on
		HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, SET);
		HAL_GPIO_WritePin(LA_GPIO_Port, LA_Pin, RESET);
		HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, SET);
		HAL_GPIO_WritePin(PR_GPIO_Port, PR_Pin, RESET);
		HAL_GPIO_WritePin(PA_GPIO_Port, PA_Pin, SET);
		HAL_GPIO_WritePin(PG_GPIO_Port, PG_Pin, SET);
		HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, SET);
		// If timer_flag[0] == 1, turn to AUTO_REDL_GREENP and set timer for the next case
		if (timer_flag[0] == 1) {
			status = AUTO_REDL_GREENP;
			setTimer(0, GREEN * 1000);
		}
		// If timer_flag[1] == 1, update traffic light duration va reset the timer
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// If timer_flag[2] == 1, turn on the next 7-segment LED and reset the timer
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// If press the MODE button, the system turn to mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 2
	case MODE2:
		// Turn on all RED light
		HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, RESET);
		HAL_GPIO_WritePin(PR_GPIO_Port, PR_Pin, RESET);
		HAL_GPIO_WritePin(LA_GPIO_Port, LA_Pin, SET);
		HAL_GPIO_WritePin(PA_GPIO_Port, PA_Pin, SET);
		HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, SET);
		HAL_GPIO_WritePin(PG_GPIO_Port, PG_Pin, SET);
		// Update  7-segment LED and clock
		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);
		// SetTimer
		setTimer(2, 250);	// Timer2 for update7SEG
		setTimer(3, 500);	// Timer3 for Blinking Led when increasing the traffic light duration
		clearTimer(0);		// Timer0 for traffic light duration (not used at mode 2)
		clearTimer(1);		// Timer1 for updateClockBufferMode1 (not used at mode 2)
		// Turn to AUTO_RED
		status = AUTO_RED;
		break;

	case AUTO_RED:
		// If timer_flag[3] == 1, toggle all RED lights and reset Timer
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LR_GPIO_Port, LR_Pin);
			HAL_GPIO_TogglePin(PR_GPIO_Port, PR_Pin);
		}
		// If timer_flag[2] == 1, turn on the next 7-segment LED, update buffer and reset Timer
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode2();
			update7SEG(index_led);
		}
		// If press the MODE button, the system turn to mode 3
		if (isButtonPressed(0) == 1) {
			status = MODE3;
		}
		// If press the INC button, increase the duration of RED lights
		if (isButtonPressed(1) == 1) {
			status = INC_RED;
			if (RED >= 99) RED = AMBER + 1;
			else RED++;
		}
		break;

	case INC_RED:
		// If timer_flag[3] == 1, toggle all RED lights and reset Timer
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LR_GPIO_Port, LR_Pin);
			HAL_GPIO_TogglePin(PR_GPIO_Port, PR_Pin);
		}
		// If timer_flag[2] == 1, turn on the next 7-segment LED, update buffer and reset Timer
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode2();
			update7SEG(index_led);
		}
		// If press the INC button, increase the duration of RED lights
		if (isButtonPressed(1) == 1) {
			if (RED >= 99) RED = AMBER + 1;
			else RED++;
		}
		// If press the SET button, duration of RED lights is fixed, return to AUTO_AMBER, and update the durations of (RED, AMBER, GREEN)
		if (isButtonPressed(2) == 1) {
			status = AUTO_RED;
			GREEN = RED - AMBER;
		}
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 3
	case MODE3:
		// Turn on all AMBER lights
		HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, SET);
		HAL_GPIO_WritePin(PR_GPIO_Port, PR_Pin, SET);
		HAL_GPIO_WritePin(LA_GPIO_Port, LA_Pin, RESET);
		HAL_GPIO_WritePin(PA_GPIO_Port, PA_Pin, RESET);
		HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, SET);
		HAL_GPIO_WritePin(PG_GPIO_Port, PG_Pin, SET);
		// Update  7-segment LED and clock
		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);
		// SetTimer
		setTimer(2, 250);	// Timer2 for update7SEG
		setTimer(3, 500);	// Timer3 for Blinking Led when increasing the traffic light duration
		clearTimer(0);		// Timer0 for traffic light duration (not used at mode 3)
		clearTimer(1);		// Timer1 for updateClockBufferMode1 (not used at mode 3)
		// Turn to AUTO_AMBER
		status = AUTO_AMBER;
		break;

	case AUTO_AMBER:
		// If timer_flag[3] == 1, toggle all AMBER lights va reset Timer
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LA_GPIO_Port, LA_Pin);
			HAL_GPIO_TogglePin(PA_GPIO_Port, PA_Pin);
		}
		// If timer_flag[2] == 1, turn on the next 7-segment LED, update buffer and reset Timer
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode3();
			update7SEG(index_led);
		}
		// If press the MODE button, the system turn to mode 4
		if (isButtonPressed(0) == 1) {
			status = MODE4;
		}
		// If press the INC button, increase the duration of AMBER lights, and turn to INC_AMBER
		if (isButtonPressed(1) == 1) {
			status = INC_AMBER;
			if (AMBER >= 5) AMBER = 1;
			else AMBER++;
		}
		break;

	case INC_AMBER:
		// If timer_flag[3] == 1, toggle all AMBER lights va reset Timer
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LA_GPIO_Port, LA_Pin);
			HAL_GPIO_TogglePin(PA_GPIO_Port, PA_Pin);
		}
		// If timer_flag[2] == 1, turn on the next 7-segment LED, update buffer and reset Timer
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode3();
			update7SEG(index_led);
		}
		// If press the INC button, increase the duration of AMBER lights, and turn to INC_AMBER
		if (isButtonPressed(1) == 1) {
			if (AMBER >= 5) AMBER = 1;
			else AMBER++;
		}
		// If press the SET button, duration of AMBER lights is fixed, return to AUTO_AMBER, and update the durations of (RED, AMBER, GREEN)
		if (isButtonPressed(2) == 1) {
			status = AUTO_AMBER;
			if (RED <= AMBER) RED = AMBER + 1;
			GREEN = RED - AMBER;
		}
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 4
	case MODE4:
		// Turn on all GREEN lights
		HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, SET);
		HAL_GPIO_WritePin(PR_GPIO_Port, PR_Pin, SET);
		HAL_GPIO_WritePin(LA_GPIO_Port, LA_Pin, SET);
		HAL_GPIO_WritePin(PA_GPIO_Port, PA_Pin, SET);
		HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, RESET);
		HAL_GPIO_WritePin(PG_GPIO_Port, PG_Pin, RESET);
		// Update  7-segment LED and clock
		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);
		// SetTimer
		setTimer(2, 250);	// Timer2 for update7SEG
		setTimer(3, 500);	// Timer3 for Blinking Led when increasing the traffic light duration
		clearTimer(0);		// Timer0 for traffic light duration (not used at mode 3)
		clearTimer(1);		// Timer1 for updateClockBufferMode1 (not used at mode 3)
		// Turn to AUTO_GREEN
		status = AUTO_GREEN;
		break;

	case AUTO_GREEN:
		// If timer_flag[3] == 1, toggle all GREEN lights va reset Timer
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LG_GPIO_Port, LG_Pin);
			HAL_GPIO_TogglePin(PG_GPIO_Port, PG_Pin);
		}
		// If timer_flag[2] == 1, turn on the next 7-segment LED, update buffer and reset Timer
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode4();
			update7SEG(index_led);
		}
		// If press the MODE button, the system turn to mode 4 1
		if (isButtonPressed(0) == 1) {
			status = MODE1;
		}
		// If press the INC button, increase the duration of GREEN lights, and turn to status INC_GREEN
		if (isButtonPressed(1) == 1) {
			status = INC_GREEN;
			if (GREEN >= RED - AMBER) GREEN = 1;
			else GREEN++;
		}
		break;

	case INC_GREEN:
		// If timer_flag[3] == 1, toggle all GREEN lights va reset Timer
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LG_GPIO_Port, LG_Pin);
			HAL_GPIO_TogglePin(PG_GPIO_Port, PG_Pin);
		}
		// If timer_flag[2] == 1, turn on the next 7-segment LED, update buffer and reset Timer
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode4();
			update7SEG(index_led);
		}
		// If press the INC button, increase the duration of GREEN lights, and turn to status INC_GREEN
		if (isButtonPressed(1) == 1) {
			if (GREEN >= RED - AMBER) GREEN = 1;
			else GREEN++;
		}
		// If press the SET button, duration of GREEN lights, return to AUTO_GREEN, and update the durations of (RED, AMBER, GREEN)
		if (isButtonPressed(2) == 1) {
			status = AUTO_GREEN;
			RED = GREEN + AMBER;
		}
		break;
//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
// DEFAULT
	default:
		break;
	}
}
