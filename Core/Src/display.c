/*
 * display.c
 *
 *  Created on: Nov 1, 2022
 *      Author: dell
 */

#include "display.h"

void display7SEG(int counter) {
	/* Initialize an array of bit values ​​to display digits from 0 to 9 */
	unsigned char disp_arr[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
	/* Initialize the variable "varr" containing the 7th bit value of the variable "counter" to display the number to be displayed and the variable "bit_var" */
	unsigned char bit_var, varr = disp_arr[counter];

	/* For each segment, the bit_var variable will take the bit value of that segment to display (0 -> On, 1 -> Off) */

	bit_var = varr & 0x01; /*SEG0 */
	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, bit_var);

	bit_var = (varr>>1) & 0x01; /*SEG1 */
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, bit_var);

	bit_var = (varr>>2) & 0x01; /*SEG2 */
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, bit_var);

	bit_var = (varr>>3) & 0x01; /*SEG3 */
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, bit_var);

	bit_var = (varr>>4) & 0x01; /*SEG4 */
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, bit_var);

	bit_var = (varr>>5) & 0x01; /*SEG5 */
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, bit_var);

	bit_var = (varr>>6) & 0x01; /*SEG6 */
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, bit_var);
}

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1,2,3,4};
void update7SEG(int index){
	display7SEG(led_buffer[index]);
	switch(index){
	case 0:
		// Display the second 7 SEG with led_buffer[0]
		index_led = 1;
		HAL_GPIO_WritePin(P1_GPIO_Port, P1_Pin, RESET);
		HAL_GPIO_WritePin(P2_GPIO_Port, P2_Pin, SET);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, SET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, SET);
		break;
	case 1:
		// Display the second 7 SEG with led_buffer[1]
		index_led = 2;
		HAL_GPIO_WritePin(P1_GPIO_Port, P1_Pin, SET);
		HAL_GPIO_WritePin(P2_GPIO_Port, P2_Pin, RESET);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, SET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, SET);
		break;
	case 2:
		// Display the third 7 SEG with led_buffer[2]
		index_led = 3;
		HAL_GPIO_WritePin(P1_GPIO_Port, P1_Pin, SET);
		HAL_GPIO_WritePin(P2_GPIO_Port, P2_Pin, SET);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, RESET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, SET);
		break;
	case 3:
		// Display the forth 7 SEG with led_buffer[3]
		index_led = 0;
		HAL_GPIO_WritePin(P1_GPIO_Port, P1_Pin, SET);
		HAL_GPIO_WritePin(P2_GPIO_Port, P2_Pin, SET);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, SET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, RESET);
		break;
	default:
		break;
	}
}


int counterL = 1, counterP = 1;
void updateClockBufferMode1() {
	// Update time value in clockBuffer
	// For 2 LED 7-SEG Landscape

	/* RED-Landscape on (count down from RED-1 -> 0) */
	if (counterL <= RED) {
		led_buffer[0] = (RED - counterL) / 10;
		led_buffer[1] = (RED - counterL) % 10;
	}
	/* GREEN-Landscape on (count down from GREEN-1 -> 0) */
	else if (counterL <= (RED + GREEN)) {
		led_buffer[0] = (RED + GREEN - counterL) / 10;
		led_buffer[1] = (RED + GREEN - counterL) % 10;
	}
	/* AMBER-Landscape on (count down from AMBER-1 -> 0) */
	else {
		led_buffer[0] = (RED + GREEN + AMBER - counterL) / 10;
		led_buffer[1] = (RED + GREEN + AMBER - counterL) % 10;
	}
	counterL++;
	/* If AMBER-Landscape is off, re-setup the counter and RED-Landscape is on again */
	if (counterL > RED + AMBER + GREEN) counterL = 1;


	// For 2 LED 7-SEG Portrait
	/* GREEN-Portrait on (count down from GREEN-1 -> 0) */
	if (counterP <= GREEN) {
		led_buffer[2] = (GREEN - counterP) / 10;
		led_buffer[3] = (GREEN - counterP) % 10;
	}
	/* AMBER-Portrait on (count down from AMBER-1 -> 0) */
	else if (counterP <= (AMBER + GREEN)) {
		led_buffer[2] = (AMBER + GREEN - counterP) / 10;
		led_buffer[3] = (AMBER + GREEN - counterP) % 10;
	}
	/* RED-Portrait on (count down from RED-1 -> 0) */
	else {
		led_buffer[2] = (RED + GREEN + AMBER - counterP) / 10;
		led_buffer[3] = (RED + GREEN + AMBER - counterP) % 10;
	}
	counterP++;
	/* If AMBER-Portrait is off, re-setup the counter and GREEN-Portrait is on again */
	if (counterP > RED + AMBER + GREEN) counterP = 1;
}

void updateClockBufferMode2() {
	// Hien thi mode 2
	led_buffer[0] = 0;
	led_buffer[1] = 2;
	// Hien thi value RED
	led_buffer[2] = RED / 10;
	led_buffer[3] = RED % 10;
}

void updateClockBufferMode3() {
	// Hien thi mode 3
	led_buffer[0] = 0;
	led_buffer[1] = 3;
	// Hien thi value AMBER
	led_buffer[2] = AMBER / 10;
	led_buffer[3] = AMBER % 10;
}

void updateClockBufferMode4() {
	// Hien thi mode 4
	led_buffer[0] = 0;
	led_buffer[1] = 4;
	// Hien thi value GREEN
	led_buffer[2] = GREEN / 10;
	led_buffer[3] = GREEN % 10;
}

