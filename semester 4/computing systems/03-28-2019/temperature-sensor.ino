void setup()
{
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(A5, INPUT);
}

void loop()
{
	static uint16_t voltage;

	voltage = analogRead(A5);
	if (voltage <= 205) {
		digitalWrite(0, LOW);
		digitalWrite(1, LOW);
		digitalWrite(2, LOW);
	} else if(voltage <= 225) {
		digitalWrite(0, HIGH);
		digitalWrite(1, LOW);
		digitalWrite(2, LOW);
	} else if(voltage <= 244) {
		digitalWrite(0, HIGH);
		digitalWrite(1, HIGH);
		digitalWrite(2, LOW);
	} else {
		digitalWrite(0, HIGH);
		digitalWrite(1, HIGH);
		digitalWrite(2, HIGH);
	}
}
