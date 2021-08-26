#include <stdio.h>
#include "progress_bar.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim2;

struct {
	uint32_t frame[FRAME_SIZE];
	uint32_t* diodes;
} progress_bar;

void initialize_bar() {
	progress_bar.diodes = progress_bar.frame + PADDING_SIZE;
}

Color COL_OFF = {0, 0, 0};
Color COL_BLUE = {0, 0, 15};
Color COL_RED = {0, 15, 0};
Color COL_GREEN = {15, 0, 0};

void print_colors() {
	for (int i = 0; i < FRAME_SIZE; ++i) {
		printf("%lu ", progress_bar.frame[i]);
	}
	printf("\n");
}

void write_binary(uint32_t * pos, char val) {
	for (int i = 0; i < 8; ++i) {
		if (val >> i) pos[7 - i] = ON_VAL;
		else pos[7 - i] = OFF_VAL;
	}
}

void set_color(int diode_id, Color color) {
	for (int i = 0; i < 3; ++i) {
		write_binary(progress_bar.diodes + diode_id * SLOTS_PER_DIODE + 8 * i, color[i]);
	}
}

void update_bar() {
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, progress_bar.frame, FRAME_SIZE);
//	print_colors();
//	HAL_Delay(20);
}

void set_color_all(Color color) {
	for (int i = 0; i < DIODES_CNT; ++i) {
		set_color(i, color);
	}
}

void clear_bar() {
	set_color_all(COL_OFF);
}

void blink(int counts, Color color) {
	for(int i=0; i<counts; i++) {
		set_color_all(color);
		update_bar();
		HAL_Delay(250);
		clear_bar();
		update_bar();
		HAL_Delay(250);
	}
}
