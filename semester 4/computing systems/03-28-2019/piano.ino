void setup()
{
	pinMode(A5, INPUT);
	pinMode(0, OUTPUT);
}

void loop()
{
	uint16_t notes[7] = {
		262*2, // C4
		294*2, // D4
		330*2, // E4
		349*2, // F4
		392*2, // G4
		440*2, // A4
		494*2  // B4
	};

	if(digitalRead(A5) == HIGH) {
		for (uint8_t i = 0; i < 7; i++) {
			tone(0, notes[i], notes[i]);
			delay(notes[i]);
		}
	}
}
