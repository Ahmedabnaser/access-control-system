/*-------------required basics-------------


variable declaration:
	type variable_name

variable initialisation:
	variable = the_first_value_to_be_assigned_to_it

function structure:
	type_of_return_value function_name (arguments_or_used_variable_from_outside_the_function)
	{
		function_code
	}

switch statement:
	choose according to (variable)
	{
		is it value1 ?
		execute code

		is it value2 ?
		execute code

		is it value3 ?
		execute code
	}




-------------layout of an Arduino function--------------

Next_state_of_the_program State()
{
	Initialize variables and LCD monitor

	while(No_input)
	{
		get input from keypad / sensor / RFID

		if (sensor_detects_motion)
			go to ALERT state
		
		if (RFID_card_detected)
			return  ADMIN state

		if (key_pressed_on_keypad)
			exit the loop
	}

	the rest of the code of the function
}



-------------used functions in the code--------------

lcd.print()
lcd.clear()
lcd.setCursor()
lcd.display()
lcd.noDisplay()

tone(pin, frequency, time)

tone(pin, frequency)
delay(time)
noTone(pin)

keypad.getKey()
digitalRead(pin)	// != cin >> pin
digitalWrite(pin, value)
*/