#ifndef __PROGRESS_BAR
#define __PROGRESS_BAR
#include "stdint.h"

#define DIODES_CNT 60
#define SLOTS_PER_DIODE 24
#define PADDING_SIZE 50
#define FRAME_SIZE (PADDING_SIZE + DIODES_CNT * SLOTS_PER_DIODE + PADDING_SIZE)
#define ON_VAL 67
#define OFF_VAL 34

typedef unsigned char Color[3];

extern Color COL_OFF;
extern Color COL_BLUE;
extern Color COL_RED;
extern Color COL_GREEN;

void print_colors();

void set_color(int diode_id, Color color);

void set_color_all(Color color);

void clear_bar();

void update_bar();

void update_progress();

void blink(int, Color);

#endif /*PROGRESS_BAR*/
