#define RED 6
#define YELLOW 5
#define GREEN 4
#define SOUND 7

void setup()
{
	pinMode(SOUND, OUTPUT);
	pinMode(RED, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(GREEN, OUTPUT);
}

void yellow_blink()
{
	tone(SOUND, 494, 2500);
	for (uint8_t i = 0; i < 3; i++) {
		digitalWrite(YELLOW, HIGH);
		delay(500);
		digitalWrite(YELLOW, LOW);
		delay(500);
	}
}

void loop()
{
	tone(SOUND, 440, 5000);
	digitalWrite(RED, HIGH);
	delay(5000);
	digitalWrite(RED, LOW);
	delay(500);
	yellow_blink();
	tone(SOUND, 523, 5000);
	digitalWrite(GREEN, HIGH);
	delay(5000);
	digitalWrite(GREEN, LOW);
	delay(500);
	yellow_blink();
}
