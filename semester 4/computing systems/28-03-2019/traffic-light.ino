#define RED 7
#define YELLOW 6
#define GREEN 5

void setup()
{
	pinMode(RED, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(GREEN, OUTPUT);
}

void yellow_blink()
{
	for (uint8_t i = 0; i < 3; i++) {
		digitalWrite(YELLOW, HIGH);
		delay(500);
		digitalWrite(YELLOW, LOW);
		delay(500);
	}
}

void loop()
{
	digitalWrite(RED, HIGH);
	delay(5000);
	digitalWrite(RED, LOW);
	delay(500);
	yellow_blink();
	digitalWrite(GREEN, HIGH);
	delay(5000);
	digitalWrite(GREEN, LOW);
	delay(500);
	yellow_blink();
}
