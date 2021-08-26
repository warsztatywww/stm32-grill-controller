#include "stm32_tm1637.h"
#include "stm32f4xx_hal.h"

int _tosterTimer;
int _run = 0;
int _finished = 0;
int _segBlink = 0;
int _blinkEnabled = 0;

void tosterDisplayInit(int brightness) {
	tm1637Init();
	tm1637SetBrightness(brightness);
}

void resetTimer() {
	_finished = 0;
	_run = 0;
	_tosterTimer = 0;
}

void tosterSetTime(int time) {
	_tosterTimer = time * 1000;
}

int tosterTimerHasFinished() {
	return _finished;
}

int getTime() {
	return _tosterTimer;
}

void tosterTimerStart() {
	_run = 1;
}

void tosterTimerBlinkMode(int blinkEnabled) {
	_blinkEnabled = blinkEnabled;
}

void tosterDisplayTime(int separator, int blinkIndex) {
	int tmp = _tosterTimer / 1000;
	int minutes = tmp / 60;
	int seconds = tmp % 60;
	if (!_segBlink) {
		blinkIndex = 0;
	}
	if(blinkIndex == 5) {
		blinkIndex = 0;
		separator = _segBlink;
	}
	tm1637DisplayDecimal(minutes*100 + seconds, separator, blinkIndex);
}

void tosterDisplayNumber(int number, int blinkIndex) {
	if (!_segBlink) {
		blinkIndex = 0;
	}
	tm1637DisplayDecimal(number, 0, blinkIndex);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (_run) {
		if (htim->Instance == TIM3) {

				if (_tosterTimer > 0) {
					_tosterTimer--;
				}
				if (_tosterTimer <= 0) {
					_finished = 1;
				}
		}
	}
	if (htim->Instance == TIM5) {
		if (_blinkEnabled) {
			_segBlink = !_segBlink;
		}
	}
}
