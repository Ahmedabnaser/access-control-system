#include "StateFunctions.h"

int From_UnlockState()
{
	// Initialize variables and LCD monitor

	tone(BUZZER_Pin, GOOD_FREQ, 400);

  unlockSolenoid();
	printNew("Unlocked", "Open for 5 sec");
	// Wait until Exit key is pressed

	startingTime = millis();
	while(key != '*' && (millis() - startingTime < 5000)) {
		key = keypad.getKey();
		delay(50);
	}

	return TO_IDLE_STATE;
}
