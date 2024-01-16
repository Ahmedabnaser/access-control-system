#ifndef STATE_FUNCTIONS_H
#define STATE_FUNCTIONS_H

/**
 * Included Arduino libraries
 */
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522Extended.h>

/**
 * Constants values used in the program
 */
#define PIR_Pin			12
#define BUZZER_Pin		13
#define LOCK_Pin		48

#define SDA_SS_Pin		53
#define RST_Pin			49

#define CARD_UID		" EB 4A 92 22"
#define TAG_UID 		" 2A 1B 6F 81"

#define GOOD_FREQ		1400
#define BAD_FREQ		1000

#define idleDuration 	30000
#define Pause 			3000
#define promptDuration	400
#define clickDuration	150

enum StatesTransition
{
	TO_IDLE_STATE,
	TO_INPUT_STATE,
	TO_UNLOCK_STATE,
	TO_ALERT_STATE,
	TO_ADMIN_STATE
};

#define ROWS 4
#define COLS 4
char keys[ROWS][COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};

/** 
 * Global variables shared in the program
 */
inline Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
inline LiquidCrystal lcd(2, 3, 14, 15, 16, 17);
inline MFRC522 RFID(SDA_SS_Pin, RST_Pin);  // Create MFRC522 instance

/**
 * Local variables used inside functions
 */
inline bool Motion_detection = true, motion_detected = false, lockState = true, validRFID_Read = false;
inline char key = NO_KEY;
inline String CORRECT_PASS = "1234", password;
inline String VALID_UID = CARD_UID, UID;
inline unsigned long startingTime;
inline int i, wrongAttempts, passlength = 4;


/**
 * States' function prototypes
 */
inline int From_IdleState();
inline int From_InputState();
inline int From_UnlockState();
inline int From_AlertState();
inline int From_AdminState();


/**
 * Useful action functions
 */
inline void unlockSolenoid() {
		digitalWrite(LOCK_Pin, LOW);
		lockState = false;
}
inline void lockSolenoid() {
		digitalWrite(LOCK_Pin, HIGH);
		lockState = true;
}
inline String& get_RFID_UID() {
	UID = "";
	// Check if a card is detected
	
	if (RFID.PICC_IsNewCardPresent() && RFID.PICC_ReadCardSerial()) {
		// Read the card UID

		for (i = 0; i < RFID.uid.size; i++) {
			UID.concat(String(RFID.uid.uidByte[i] < 0x10 ? " 0" : " "));
			UID.concat(String(RFID.uid.uidByte[i], HEX));
		}
		UID.toUpperCase();
	}	
	return UID;
}

inline void printNew(const String& line1, const String& line2) {
	lcd.clear();
	lcd.print(line1);
	lcd.setCursor(0, 1);
	if (line2 != "")
		lcd.print(line2);
}
#endif
