#include "progress_display.h"
#include "progress_bar.h"
#include "color.h"
#include <string.h>

int current_bar_pos = 0;
int time_per_tick;
int sleep_time;
int start_time;

int getTime();

void clear_progress() {
	current_bar_pos = 0;
	clear_bar();
}

Color COL_PROGRESS;
Color COL_PROGRESS_HSL = {100, 255, 10};

void update_progress() {
	COL_PROGRESS_HSL[0] += 6;
	HSLToRGB(COL_PROGRESS_HSL, COL_PROGRESS);
	set_color(current_bar_pos++, COL_PROGRESS);
	printf("%d %d %d | %d %d %d\n", COL_PROGRESS_HSL[0], COL_PROGRESS_HSL[1], COL_PROGRESS_HSL[2], COL_PROGRESS[0], COL_PROGRESS[1], COL_PROGRESS[2]);
}

void update_up_to(int pos) {
	while (current_bar_pos < pos) {
		update_progress();
	}
}

void run_progress_bar(int runtime) {
	time_per_tick = (runtime) / DIODES_CNT;
	sleep_time = (runtime / 10) / DIODES_CNT;
	start_time = getTime();
	clear_progress();
	update_bar();
}

void dupa() {
	int enlapsed_time = start_time - getTime();
	update_up_to(enlapsed_time / time_per_tick);
	update_bar();
}
