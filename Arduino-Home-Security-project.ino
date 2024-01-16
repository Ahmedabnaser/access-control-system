#include "StateFunctions.h"

#include "IdleState.h"
#include "InputState.h"
#include "UnlockState.h"
#include "AlertState.h"
#include "AdminState.h"


int Next_Program_State;

void setup()
{
	// Initialize arduino pin modes

	pinMode(PIR_Pin, INPUT_PULLUP);
	pinMode(BUZZER_Pin, OUTPUT);
	pinMode(LOCK_Pin, OUTPUT);

	lcd.begin(16, 2);		// Initialize LCD rows & columns
	lcd.print("Bismillah"); // بنسمي الله
	SPI.begin();			// Initialize SPI bus
	RFID.PCD_Init();		// Initialize RFID device

	// Initialize the Program's state

	Next_Program_State = TO_IDLE_STATE;
}

void loop()
{ /**/
	switch (Next_Program_State)
	{
	case TO_IDLE_STATE:
		Next_Program_State = From_IdleState();
		break;
	case TO_INPUT_STATE:
		Next_Program_State = From_InputState();
		break;
	case TO_UNLOCK_STATE:
		Next_Program_State = From_UnlockState();
		break;
	case TO_ALERT_STATE:
		Next_Program_State = From_AlertState();
		break;
	case TO_ADMIN_STATE:
		Next_Program_State = From_AdminState();
		break;
	}
  /** /
    digitalWrite(LOCK_Pin,LOW); // RELAY ON   
  delay(1000);   
  digitalWrite(LOCK_Pin,HIGH); // RELAY OFF   
  delay(1000); 
  /**/  
}