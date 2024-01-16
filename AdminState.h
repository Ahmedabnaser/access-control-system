#include "StateFunctions.h"
#include <ctype.h>

int From_AdminState()
{
	// Initialize variables and LCD monitor

	noTone(BUZZER_Pin);
	motion_detected = false;

	tone(BUZZER_Pin, GOOD_FREQ, promptDuration);
	printNew("ADMIN: options", " -A -B -C '*'");
	while (true)
	{
		key = NO_KEY;
		// Wait in a loop until user presses a key

		while(key != '*' && key != 'A' && key != 'B' && key != 'C') {
      		// digitalWrite(LOCK_Pin, HIGH);
			key = keypad.getKey();
			delay(50);
		}

		switch(key)
		{
		case '*':
			return TO_IDLE_STATE;
		case 'A': {
			// Turn On/Off alarm functionality
			if (Motion_detection == true)
				printNew("Turn sensor Off", "1-yes 2-no");
			else
				printNew("Turn sensor On", "1-yes 2-no");
			while (key != '1' && key != '2')
				key = keypad.getKey(), delay(50);
			if (key == '1')
				Motion_detection = !Motion_detection;
			return TO_ADMIN_STATE;
		}
		case 'B': {
			// Change valid admin RFID
			printNew("Change UID?", "1-yes 2-no");
			while (key != '1' && key != '2')
				key = keypad.getKey(), delay(50);
			if (key == '1') {
				printNew("Set new UID", "(pass the card)");
				VALID_UID = "";
				while (VALID_UID == "")
					VALID_UID = get_RFID_UID();
				printNew("New UID", VALID_UID);
				delay(Pause);
			}
			return TO_ADMIN_STATE;
		}
		case 'C': {
			// Change password
			printNew("Change pass?", "1-yes 2-no");
			while (key != '1' && key != '2')
				key = keypad.getKey(), delay(50);
			if (key == '1') {
				passlength = 0;
				CORRECT_PASS = "";
				printNew("pass len: (2-16)", "");
				key = NO_KEY;
				while (!isdigit(key) || key == '0') {
					key = keypad.getKey(), delay(50);
				}
				if (key == '1') {
					passlength += 10;
					lcd.print(key);
					key = NO_KEY;
					while (!isdigit(key) || key > '6') {
						key = keypad.getKey(), delay(50);
					}
				}
				passlength += key - '0';
				lcd.print(key);
				delay(500);
				lcd.clear();
				lcd.print("New password:");
				lcd.setCursor(0, 1);
				for (i = 0; i < passlength; i++) {
					key = NO_KEY;
					while (key == NO_KEY)
						key = keypad.getKey(), delay(50);
					lcd.print(key);
					CORRECT_PASS += key;
				}
				delay(Pause);
			}
			return TO_ADMIN_STATE;
		}
		}
	}
}