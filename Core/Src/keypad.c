#include "stm32f4xx.h"

char keys[3][4] = {
		{'1','4','7','*'},
		{'2','5','8','0'},
		{'3','6','9','#'}
			};

uint16_t pinsOut[3] = {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10};
uint16_t pinsIn[4] = {GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};

char scan() {
	char ret = 'x';
	for(uint16_t pinOut = 0; pinOut <= 2; pinOut++) {
		HAL_GPIO_WritePin(GPIOA, pinsOut[pinOut], GPIO_PIN_SET);
		for(uint16_t pinIn = 0; pinIn <= 3; pinIn++) {
			if( HAL_GPIO_ReadPin(GPIOB, pinsIn[pinIn]) ) {
				ret = keys[pinOut][pinIn];
			}
		}
		HAL_GPIO_WritePin(GPIOA, pinsOut[pinOut], GPIO_PIN_RESET);
		HAL_Delay(1);
	}

	return ret;
}

char lastKey = 'x';
int enteredNumber = 0;
int letter = 0;
int powers[4] = {1000, 100, 10, 1};
int ready = 0;
int setTime = 0;

void updateKeypad() {
	char currentKey = scan();

	if(currentKey != lastKey && currentKey != 'x') {
		if(currentKey == '*') {
			enteredNumber = 0;
			letter = 0;
		} else if(currentKey == '#') {
			ready = 1;
		} else if(letter < 4) {
			if(setTime == 0 || (!(letter == 2 && currentKey >= '6'))) {
				enteredNumber += powers[letter] * (currentKey - '0');
				letter++;
			}
		}
	}
	lastKey = currentKey;
}

void resetKeypad() {
	letter = 0;
	enteredNumber = 0;
}

int checkReadiness() {
	if(ready) {
		ready = 0;
		return enteredNumber;
	} else {
		return -1;
	}
}

int checkNumber() {
	return enteredNumber;
}

int checkLetter() {
	return letter;
}

void keypadEnterTime(int x) {
	setTime = x;
}

//		  text[letter] = currentKey;
//		  letter++;
//		  if(letter == 4) {
//			  if(text[0] == password[0] && text[1] == password[1] && text[2] == password[2] && text[3] == password[3]) {
//				  unlocked = 1;
//				  letter = 0;
//			  } else {
//				  letter = 0;
//			  }
//		  }
//	  }
//	  if(unlocked) {
//		  if((time % 13) == 0)
//			  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
//	  } else {
//		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
//	  }
//	  lastKey = currentKey;
//	  time++;

	  //printf("%c\n",scan());
