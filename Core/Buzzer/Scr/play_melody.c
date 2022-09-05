#include "melody.h"
#include "main.h"
#include "tim.h"

uint32_t tone_iter = 0;
volatile uint32_t tone_delay = 20;

void buzzerSetNewFrequency(uint32_t newFreq) {
	uint64_t tempFreq = newFreq;
	if(newFreq == 0) tempFreq = 1;

	uint64_t tempNewValue = (uint64_t) CPU_FREQ / PRESCALER / tempFreq;

	TIM4 ->ARR = (uint32_t)tempNewValue;
	TIM4 -> CCR4 = (uint32_t)tempNewValue/2;

}

void play_melody() {
  ++tone_iter;
  uint8_t temp = sizeof(marioMelody)/sizeof(marioMelody[0]);
  if (tone_iter < temp) {
	  buzzerSetNewFrequency(marioMelody[tone_iter]);
	  tone_delay = marioDuration[tone_iter] * melodySlowfactor[0];
  }
  else {
	  tone_delay = 3000;
	  tone_iter = 0;
  }
}
