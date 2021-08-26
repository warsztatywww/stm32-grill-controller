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
Color COL_BLUE = {0, 0, 115};
Color COL_RED = {0, 115, 0};
Color COL_GREEN = {115, 0, 0};
Color COL_YELLOW = {50, 115, 0};

void print_colors() {
	for (int i = 0; i < FRAME_SIZE; ++i) {
		printf("%lu ", progress_bar.frame[i]);
	}
	printf("\n");
}

void write_binary(uint32_t * pos, char val) {
	for (int i = 0; i < 8; ++i) {
		if ((1 << i) & val) pos[7 - i] = ON_VAL;
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

struct {
	int frames_displayed;
	int starting_time;
	int time_per_frame;
	int is_running;
} shift_animation;

void initialize_shift_animation(int time_per_frame) {
	shift_animation.is_running = 1;
	shift_animation.frames_displayed = 0;
	shift_animation.starting_time = getTime();
	shift_animation.time_per_frame = time_per_frame;
}

void is_shift_initialized() {
	return shift_animation.is_running;
}

void stop_shift_animation() {
	return shift_animation.is_running = 0;
}

void update_shift_animation() {
	int passed_time = getTime() - shift_animation.starting_time;
	if (passed_time > shift_animation.time_per_frame * shift_animation.frames_displayed) {
		shift_bar(1);
		update_bar();
		shift_animation.frames_displayed++;
	}
}

void shift_bar(int step) {
	uint32_t* temp;
	for(int i=0; i<DIODES_CNT*SLOTS_PER_DIODE; ++i) {
		temp[(i + step * SLOTS_PER_DIODE) % DIODES_CNT*SLOTS_PER_DIODE] = progress_bar.diodes[i];
	}
	memcpy(progress_bar.diodes, temp, DIODES_CNT*SLOTS_PER_DIODE);
}
