#include "StateFunctions.h"

int From_IdleState()
{
	// Initialize variables and LCD monitor

	lcd.noDisplay();
	lockSolenoid();
	key = NO_KEY;

	// Wait in a loop until user presses Start '#'

	while (key != '#') {
		key = keypad.getKey();
		motion_detected = digitalRead(PIR_Pin);
		// Check if the sensor detected motion

		if (Motion_detection == true && motion_detected == LOW)
			return TO_ALERT_STATE;
		delay(50);
	}
	// Program started go to use input

	return TO_INPUT_STATE;
}
