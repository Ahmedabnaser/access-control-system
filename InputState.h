#include "StateFunctions.h"


int From_InputState()
{
	// Initialize variables and LCD monitor

	wrongAttempts = 0;
	lcd.display();
	tone(BUZZER_Pin, GOOD_FREQ, promptDuration);
	printNew("Enter Password:", "");
	lcd.blink();
	password = "";

	while (true)
	{
		key = NO_KEY;
		startingTime = millis();
		// Wait in a loop until user presses a key

		while (key == NO_KEY) {
			key = keypad.getKey();
			validRFID_Read = (get_RFID_UID() == VALID_UID);
			motion_detected = digitalRead(PIR_Pin);
			// Check for a valid RFID
			
			if (validRFID_Read)
				return TO_ADMIN_STATE;
			// Check if idle duration is exceeded
			
			if (millis() - startingTime > idleDuration)
				return TO_IDLE_STATE;
			// Check if the sensor detected motion

			if (Motion_detection == true && motion_detected == LOW)
				return TO_ALERT_STATE;
			delay(50);
		}

		// Key pressed and recorded
		
		password += key;
		tone(BUZZER_Pin, GOOD_FREQ, clickDuration);
		lcd.print('*');

		if (password.length() == CORRECT_PASS.length()) {
			if (password == CORRECT_PASS) {
				// Set to unlocked state

				lcd.noBlink();
				printNew("Correct Pass", "");
				delay(Pause);
				return TO_UNLOCK_STATE;
			} else if (wrongAttempts < 2) {
				// Warn the user and retry

				wrongAttempts++;
				tone(BUZZER_Pin, BAD_FREQ , promptDuration);
				printNew("Incorrect Pass", String(3 - wrongAttempts) + String(" attempts left"));
				delay(Pause);
				printNew("Enter Password:", "");
				password = "";
			} else {
				// Set to alert state
				
				lcd.noBlink();
				return TO_ALERT_STATE;
			}
		}
	}
}