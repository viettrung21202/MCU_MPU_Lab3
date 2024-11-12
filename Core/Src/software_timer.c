/*
 * software_timer.c
 *
 *  Created on: Sep 30, 2022
 *      Author: Admin
 */

#include "software_timer.h"

int TIME_CYCLE; // Time cycle

// Initialize the timer_counter and timer_flag arrays with the number of elements each equal to NUM_OF_TIMERS
int timer_counter[NUM_OF_TIMERS] = {0};
int timer_flag[NUM_OF_TIMERS] = {0};

void setTimer(int index, int duration) {
	timer_counter[index] = duration / TIME_CYCLE;
	timer_flag[index] = 0;
}

void clearTimer(int index) {
	timer_counter[index] = 0;
	timer_flag[index] = 0;
}

void timerRun(){
	for (int i = 0; i < NUM_OF_TIMERS; i++) {
		if (timer_counter[i] > 0){
			timer_counter[i]--;
			if (timer_counter[i] <= 0){
				timer_flag[i] = 1;
			}
		}
	}
}
