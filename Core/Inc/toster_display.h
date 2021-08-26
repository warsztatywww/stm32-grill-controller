#pragma once

void tosterDisplayInit(int brightness);
void tosterSetTime(int time);
int tosterTimerHasFinished();
void tosterTimerStart();
void tosterDisplayTime(int separator, int blinkIndex);
void tosterDisplayTime(int number, int blinkIndex);
void tosterTimerBlinkMode(int blinkEnabled);
int getTime();
