#include "StateFunctions.h"

int From_AlertState()
{
	// Initialize variables and LCD monitor

	lcd.display();
	lcd.clear();
	lcd.print("Access Denied");
	tone(BUZZER_Pin, BAD_FREQ);
	validRFID_Read = false;

	if (motion_detected == HIGH) {
		lcd.setCursor(0, 1);
		lcd.print("INTRUDER");
	}

	// Wait until valid RFID is detected

	while (!validRFID_Read) {
		validRFID_Read = (get_RFID_UID() == VALID_UID);
		key = keypad.getKey();
		delay(50);
	}

	// Go to admin mode

	return TO_ADMIN_STATE;
}